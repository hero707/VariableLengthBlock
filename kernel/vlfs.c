#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/fs.h>
#include <linux/file.h>

asmlinkage long sys_vlfs_modify(int fd, unsigned long offset, size_t len)
{
	struct file *file;

	printk(KERN_ALERT "sys_vlfs_modify function call(fd : %d offset : %d len : %d\n", fd, offset, len);
	if(fd < 0){
		printk("file error\n");
	}
	file = fget(fd);
	
//	printk("i_mode : %d\n", file->f_inode->i_mode);
//	printk("i_uid : %d\n", file->f_inode->i_uid);
//	printk("i_size : %d\n", file->f_inode->i_size);
	printk("-------------------------------------\n");
	printk("i_vb_count : %d\n", file->f_inode->i_vb_count);
	printk("offset : %d\n", offset);
	printk("offset >> 12 : %d\n", offset>>12);

	file->f_inode->i_vb[file->f_inode->i_vb_count].vb_index = offset >> 12;
	printk("i_vb[count] : %d\n", file->f_inode->i_vb[file->f_inode->i_vb_count]);
	if(file->f_inode->i_vb_count < I_VB_MAX){
		printk("new vb index\n");
		file->f_inode->i_vb_count++;
	}else{
		file->f_inode->i_vb_count = 0;
	}
	printk("i_vb_count : %d\n", file->f_inode->i_vb_count);
	printk(KERN_ALERT "sys_vlfs_modify function finish\n");
	printk("-------------------------------------\n");
	return 1;
}
