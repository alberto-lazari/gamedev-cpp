#pragma once

const char* sprintf(const char* format, ...);

const char* join(const char* s1, const char* s2);

const char** split(const char* string, char split_c);

bool matches(const char* string, const char* pattern);

void flog(const char* file_path, const char* string);
