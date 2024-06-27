#pragma once

wchar_t** allocate_memory_for_text();

void free_memory(wchar_t** dyn_strs, int len);