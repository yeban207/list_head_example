#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>

#define LOG(msg) \
	do {\
		printk(KERN_ALERT msg);\
		} while(0)
		

struct student {
	char name[100];
	int num;
	struct list_head list;
};

struct student *pstudent;
struct student *tmp_student;
struct list_head studnet_list;
struct list_head *pos;
static int __init mylist_init(void)
{
	int i = 0;

	INIT_LIST_HEAD(&studnet_list);

	pstudent = kmalloc(sizeof(struct student) * 5, GFP_KERNEL);
	if (pstudent) {
		LOG("application memory success!\n");
	} else {
		LOG("application memory fail!\n");
		return -1;
	}

	memset(pstudent, 0, sizeof(struct student) * 5);


	for (i= 0; i < 5; i++)
	{
		sprintf(pstudent[i].name, "student%d", i+1);
		pstudent[i].num = i + 1;
		list_add(&(pstudent[i].list), studnet_list);
	}
	
	list_for_each(pos, &studnet_list)
	{
		tmp_student = list_entry(pos, struct student, list);
		if (tmp_student) {
			LOG("get student node success!\n");
		} else {
			LOG("get student node fail!\n");
			kfree(pstudent);		
			return -2;
		}
		printf(KERN_ALERT "studet %d, name = %s\n", tmp_student->num, tmp_student->name);
	}

	return 0;
}

static void __exit mylist_exit(void)
{
	printf(KERN_ALERT "mylist_head module uninstall!\n");
	int i;
	for (i = 0; i < 5; i++)
	{
		list_del(&(pstudent[i].list));
	}
	kfree(pstudent);
}

module_init(mylist_init);
module_exit(mylist_exit);
MODULE_LICENSE("GPL v2");
MOUDE_AUTHOR("LJQ");
MODUEL_DESCRIPTION("a sample list_head example!");
MODULE_ALIAS("list_head example!");
