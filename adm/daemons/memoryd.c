#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>

int reboot_now = 0;
int clean_up() { return 1; }

void auto_relaim();
//void auto_relaim1();

void create()
{
        seteuid(ROOT_UID);
        set("name", HIR "ϵͳ����" NOR);
        set("channel_id", "�ڴ澫��");
        CHANNEL_D->do_channel( this_object(), "sys", "�ڴ澫���Ѿ�������");
        //call_out("auto_relaim1", 1);
        call_out("auto_relaim", 30);
}
//Timer reboot added by mike 
void auto_relaim()
{
        int i;      
                int t;
                int x;
                int RBday=20;   //�趨���������RBday
                int RBtime=22;  //�趨����ʱ��RBtime
        string str;
        mixed *timer;

        x = uptime();
        x /= 60;
        x /= 60;
        x /= 24;

        timer=localtime(time());
        t=timer[2];

        if (i = reclaim_objects())
             //   CHANNEL_D->do_channel( this_object(), "sys",
            //            sprintf("ϵͳ�Զ���� %d ��������", i));
                    if (t == RBtime && ! "/cmds/arch/reboot"->is_rebooting() && x==RBday)//modify reboot's time to 22
        {
            reboot_now = 10;
            str = "/cmds/usr/uptime"->main("-r");
            "/cmds/arch/reboot"->main(this_object(), "after 10 called by memoryd");
            log_file("sys_reboot", "system rebooting : " + str);
    cp("/log/debug.log","/drive/debug.log");//����debug.logΪsysterm.logΪ������;
        }

        remove_call_out("auto_relaim");
          call_out("auto_relaim", 600);



        __DIR__"qdeld"->qdel();
        
}
/*
void auto_relaim1()
{
        int x;      
    
        if (x = reclaim_objects())
                CHANNEL_D->do_channel( this_object(), "sys",
                        sprintf("ϵͳ�Զ���� %d ��������", x));

        remove_call_out("auto_relaim1");
                  call_out("auto_relaim1", 30);
}
*/


