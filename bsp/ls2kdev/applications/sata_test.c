/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-17     maoxiaochuan    first version
 */

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <ext4.h>
#include <ext4_debug.h>
#include <blk_device.h>

void mount_ssd(int argc, char **argv)
{
    if (argc < 3)
    {
        rt_kprintf("usage: mount_ssd path part_id [debug,such as print all partition]\neg: mount_ssd / 0 [1]\n");
        return;
    }

    struct blk_device *blkdev = (struct blk_device *)rt_device_find("dwc_ahsata_blk");
    if(blkdev == RT_NULL)
    {
        rt_kprintf("dwc_ahsata_blk not found!\n");
        return;
    }
    
    blk_device_init(blkdev);

    if (argc == 4) 
    {
        int show = atoi(argv[3]);
        if (show)
        {
            ext4_dmask_set(DEBUG_ALL);
        }
        else
        {
            ext4_dmask_clr(DEBUG_ALL);
        }
	
    }
    
    char *path = argv[1];
    int part_id = atoi(argv[2]);
    int ret = dfs_mount("dwc_ahsata_blk", path, "ext", 0, (void *)part_id);
    rt_kprintf("dwc_ahsata_blk mount / ext,ret:%d , errno:%d!\n", ret, rt_get_errno());
}
MSH_CMD_EXPORT(mount_ssd, mount ssd parition);

