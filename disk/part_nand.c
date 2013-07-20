/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Support for harddisk partitions.
 *
 * To be compatible with LinuxPPC and Apple we use the standard Apple
 * SCSI disk partitioning scheme. For more information see:
 * http://developer.apple.com/techpubs/mac/Devices/Devices-126.html#MARKER-14-92
 */

#include <common.h>
#include <command.h>

#if defined(CONFIG_CMD_NAND)

/*
 * Test for a valid NAND partition
 */
int test_part_nand (block_dev_desc_t *dev_desc)
{
	return (0);
}


void print_part_nand (block_dev_desc_t *dev_desc)
{
	int i;
	printf("partition   size\n");
	for (i = 1;; i++) {
		dev_desc = nand_get_dev(i - 1);
		if (dev_desc->lba == -1)
			break;
		printf("%d    %8lu\n", i, dev_desc->lba);
	}
	return;
}

int get_partition_info_nand (block_dev_desc_t *dev_desc, int part, disk_partition_t *info)
{
	debug("get_partition_info_nand: part = %d, ", part);
	info->start = 0;
	dev_desc = nand_get_dev(part - 1);
	info->size = dev_desc->lba;
	info->blksz = dev_desc->blksz;
	sprintf ((char *)info->type, "U-Boot");
	debug("start = %lu, size = %lu, blksz = %lu\n", info->start, info->size, info->blksz);
	return (0);
}

#endif
