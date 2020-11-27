// changanjob.c  供查阅长安府任务完成情况的指令

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me)
{        
        mapping q;

        if (me->query("changanjob_count"))
        write(sprintf("你已经连续完成了 %d 个长安府任务，继续加油努力啊！\n",
                     me->query("changanjob_count")));

        if (! mapp(q = me->query("changanjob")))        
        return notify_fail("你现在没有领取长安府的任务！\n");             

        q =  me->query("changanjob");

                switch (q["kind"])
        {

           case "whisper":
                write("目前知府让你去把一个暗号传给"HIY +
                q["place"] + NOR "的" HIY +  q["target"]
                + NOR"。\n");
                return 1;

           case "patrol":                
                write("目前知府让你去长安城里巡城。\n");
                return 1;

           case "hunt":                
                write("目前知府让你去长安城里杀野兽保护百姓。\n");
                return 1;  
        }

        write("你现在没有领取长安府的任务！\n");
        return 1;
}



int help(object me)
{
        write(@HELP
这个指令可以用来查阅你完成长安府任务的情况。
HELP );
        return 1;
}

