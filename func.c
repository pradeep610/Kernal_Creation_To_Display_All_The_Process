#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched/signal.h>
#include<linux/sched.h>//it contains the task_struct structure
//task_struct is a C structure, that acts as a process descriptor,it contains all the information that is required by the kernel
struct task_struct *task;//parent info
struct task_struct *task_child;//child info
struct list_head *list;

int iterate_init(void)
{	
	for_each_process(task)//for each process in task
	{
		printk(KERN_INFO "\n Parent PID: %d  PROCESS: %s STATE: %ld",task->pid, task->comm,task->state);//task->comm is used for printing the process information
		list_for_each(list, &task->children)
		{
			task_child = list_entry(list,struct task_struct, sibling);//it is used to return a pointer to the data structure of "type" , which contains "messaage" fo type "list"
			printk(KERN_INFO "\n\t\tCHILD of %s[%d] PID: %d PROCESS: %s STATE: %ld", task->comm, task->pid, task_child->pid, task_child->comm, task_child->state);
		}
		printk("----------------------------------------------------------------------------------------------------------");
	}
	return 0;
}

void cleanup_exit(void)
{
	printk(KERN_INFO "%s","REMOVING MODULE\n");
}

module_init(iterate_init);
module_exit(cleanup_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUNDEEP A");
//PID 0 is an idle process, This process is a part of the kernel and is not a regular user-mode process.
//The init process owns PID 1 and is solely responsible for starting and shutting down the system. 
