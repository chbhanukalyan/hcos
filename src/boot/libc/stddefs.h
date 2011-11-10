/*
 * Copyright (C) 2011  Bhanu Chetlapalli
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * =========================================================================
 *
 * This File is a part of the Holy Cow Operating System, which is written and
 * maintained by Bhanu Kalyan Chetlapalli <chbhanukalyan@gmail.com>.
 *
 * This file contains the various generic function declarations
 */

#ifdef __cplusplus
extern "C" {
#endif

extern void clearscreen(void);
extern void print_msg(const char *msg);
extern int strlen(const char *str);
extern void *memset(void *s, int c, int n);
extern void *memcpy(void *d, const void *s, int n);
extern char* strncpy(char *d, const char *s, int n);

extern int printf(const char *, ...);

#ifdef __cplusplus
}
#endif

