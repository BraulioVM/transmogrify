#include <transmogrify.h>

#include <fmt/format.h>

#include <cstdint>
#include <limits>
#include <string_view>

#include <unistd.h>
#include <sys/mman.h>

// Defined in the assembly code
extern void* assembly_stub;

void *transmogrify_return; // needed for jumping back
void *transmogrify_hook;


namespace transmogrify {

namespace {

int get_page_size()
{
    return sysconf(_SC_PAGE_SIZE);
}

template<typename Ptr>
std::size_t as_number(Ptr ptr)
{
    return reinterpret_cast<std::size_t>(ptr);
}

template<typename Ptr>
void* as_void_ptr(Ptr ptr)
{
    return reinterpret_cast<void*>(ptr);
}

void* align_ptr(void* ptr, int alignment)
{
    std::size_t n = as_number(ptr);
    std::size_t aligned = n & ~(alignment - 1);
    return as_void_ptr(aligned);
}

bool mark_memory_page_as_writable(void_function target)
{
    void* target_ptr = as_void_ptr(target);
    int page_size = get_page_size();
    
    void* page_aligned_ptr = align_ptr(target_ptr, page_size);

    int result =
        ::mprotect(page_aligned_ptr,
                   page_size * 2, // function could cross page boundary
                   PROT_READ | PROT_WRITE | PROT_EXEC);

    return result == 0;
}

unsigned char preamble[] =
    { 0xf3, 0x0f, 0x1e, 0xfa, // endbr64
      0x55, // push %rbp
      0x48,  0x89, 0xe5 // mov    %rsp,%rbp
    };
std::basic_string_view<unsigned char> overridable_preamble(preamble,
                                                           sizeof(preamble));

bool begins_with_overridable_preamble(void_function target)
{
    auto* target_ptr = (unsigned char*)as_void_ptr(target);

    std::basic_string_view<unsigned char> target_function_beginning(
        target_ptr,
        overridable_preamble.size());

    return overridable_preamble == target_function_beginning;
}

bool hook_with_jump_to_stub(void_function target, void* stub)
{
    const std::size_t jmp_instruction_length = 5;
    const std::size_t offset =
        as_number(stub) - as_number(target) - jmp_instruction_length;

    if (offset > std::numeric_limits<int>::max()) {
        return false;
    } 

    int offset32 = static_cast<int>(offset);
    
    unsigned char* target_code = (unsigned char*)as_void_ptr(target);
    unsigned char jmp = 0xe9;
    *target_code = jmp;
    std::memcpy(target_code + 1,
                reinterpret_cast<char*>(&offset32),
                sizeof(offset32));

    return true;
}

}


bool hook(void_function target,
          void_function hook)
{
    if (!mark_memory_page_as_writable(target))
    {
        fmt::print("couldn't mark memory as writable\n");
        return false;
    }

    if (!begins_with_overridable_preamble(target))
    {
        fmt::print("the function doesn't begin with overridable preamble\n");
        return false;
    }

    if (!hook_with_jump_to_stub(target, &assembly_stub))
    {
        return false;
    }

    transmogrify_hook = as_void_ptr(hook);
    transmogrify_return = (char*)as_void_ptr(target) + overridable_preamble.size();

    return true;
}
}
