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
; This contains the include definitions for accessing the hard disk in
; order to load the third stage of the bootloader.

; Define the hard disk controler IDs
%define		HARD_DISK_PRIMARY_CONTROLER		0x01F0
%define		HARD_DISK_SECONDARY_CONTROLER   0x0170

; Note that this will read sectors without any limit
%define		HD_CTRLR_READ_SECTORS		0x20
%define		HD_CTRLR_WRITE_SECTORS		0x30

; List of Registers on the hard disk controller, which control what data we
; want to retrieve from the controller and which device
%define		PIOREG_DATA_WORD		0	
%define		PIOREG_SECTOR_BYTE		2
%define		PIOREG_LBA_LOW_BYTE		3
%define		PIOREG_LBA_MID_BYTE		4
%define		PIOREG_LBA_HIGH_BYTE	5
%define		PIOREG_DEVICE_BYTE		6
%define		PIOREG_COMMAND_BYTE		7

; Define the various locations that can be written to, to access the 
; harddisk internal registers
%define		HDPC_DATA_WORD			(HARD_DISK_PRIMARY_CONTROLER + PIOREG_DATA_WORD)
%define		HDPC_SECTOR_BYTE		(HARD_DISK_PRIMARY_CONTROLER + PIOREG_SECTOR_BYTE)
%define		HDPC_LBA_LOW_BYTE		(HARD_DISK_PRIMARY_CONTROLER + PIOREG_LBA_LOW_BYTE)
%define		HDPC_LBA_MID_BYTE		(HARD_DISK_PRIMARY_CONTROLER + PIOREG_LBA_MID_BYTE)
%define		HDPC_LBA_HIGH_BYTE		(HARD_DISK_PRIMARY_CONTROLER + PIOREG_LBA_HIGH_BYTE)
%define		HDPC_DEVICE_BYTE		(HARD_DISK_PRIMARY_CONTROLER + PIOREG_DEVICE_BYTE)
%define		HDPC_COMMAND_BYTE		(HARD_DISK_PRIMARY_CONTROLER + PIOREG_COMMAND_BYTE)

%define		HDSC_DATA_WORD			(HARD_DISK_SECONDARY_CONTROLER + PIOREG_DATA_WORD)
%define		HDSC_SECTOR_BYTE		(HARD_DISK_SECONDARY_CONTROLER + PIOREG_SECTOR_BYTE)
%define		HDSC_LBA_LOW_BYTE		(HARD_DISK_SECONDARY_CONTROLER + PIOREG_LBA_LOW_BYTE)
%define		HDSC_LBA_MID_BYTE		(HARD_DISK_SECONDARY_CONTROLER + PIOREG_LBA_MID_BYTE)
%define		HDSC_LBA_HIGH_BYTE		(HARD_DISK_SECONDARY_CONTROLER + PIOREG_LBA_HIGH_BYTE)
%define		HDSC_DEVICE_BYTE		(HARD_DISK_SECONDARY_CONTROLER + PIOREG_DEVICE_BYTE)
%define		HDSC_COMMAND_BYTE		(HARD_DISK_SECONDARY_CONTROLER + PIOREG_COMMAND_BYTE)

