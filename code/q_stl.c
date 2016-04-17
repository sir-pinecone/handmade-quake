#include "quakedef.h"


uint32 Q_strlen(const char *str) {
  uint32 count = 0;
  while (str[count]) {
    ++count;
  }
  return count;
}

void Q_strcpy(char *dest, const char *src) {
  while (*dest = *src) {
    ++dest;
    ++src;
  }
}

void Q_strncpy(char *dest, const char *src, int32 count) {
  if (count < 0) {
    return;
  }

  while (count && (*dest = *src)) {
    ++dest;
    ++src;
    --count;
  }

  while (count) {
    *dest = 0;
    ++dest;
    --count;
  }
}

int32 Q_strcmp(const char *s1, const char *s2) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;
  while (*p1 == *p2) {
    if (!*p1) {
      return 0;
    }
    ++p1;
    ++p2;
  }
  return ((*p1 < *p2) ? -1 : 1);
}

/* Custom string to number coercion. Supports signed decimal or hex values. */
int32 Q_atoi(const char *str) {
  int32 sign = 1;
  int32 val = 0;
  char c;

  if (!str) {
    return 0;
  }

  if (*str == '-') {
    sign = -1;
    ++str;
  }

  // hex
  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
    str += 2;
    while (1) {
      c = *str;
      ++str;
      if (c >= '0' && c <= '9') {
        val = val * 16 + (c - '0');
      }
      else if (c >= 'a' && c <= 'f') {
        val = val * 16 + c - 'a' + 10;
      }
      else if (c >= 'A' && c <= 'F') {
        val = val * 16 + c - 'A' + 10;
      }
      else {
        return sign * val;
      }
    }
  }

  // decimal
  while (1) {
    c = *str;
    ++str;
    if (c < '0' || c > '9') {
      return sign * val;
    }
    val = val * 10 + (c - '0'); // '0' is 48 so c - '0' gives us the numerical version of the ascii number.
  }
}
