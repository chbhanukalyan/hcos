; Copyright (C) 2009  Bhanu Chetlapalli
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
; =========================================================================
;
; This File is a part of the Holy Cow Operating System, which is written and
; maintained by Bhanu Kalyan Chetlapalli <chbhanukalyan@gmail.com>.
; 
; This contains the include definitions, which are shared between the
; first and second stages of the boot loader.

%define	SECOND_STAGE_SIZE           1
%define	SECOND_STAGE_LOAD_SEGMENT   0500h

%define	THIRD_STAGE_LOAD_ADDRESS	0x000E0000
