#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "\n\n                ��        ��        ��" NOR);
        set("long", HIG "\n"
"������ԭ��ӡ��Զ������֮һ������Ϊ�����������ͺö���\n"
"���񣬾�����������������ݡ����и�����û�е����е�˵��\n"
"ֻ�ǽ�����������У���˵�Ƕ�������ˣ���������̽�����\n"
"Ϊ�Ƶ����ϴ��������������С��������ˣ��·����ˡ���\n"
"�������������(canwu)��\n\n" NOR);
set("exits", ([ 
            "out"   : "/d/special/taixu",            
        ]));
        setup();
}

void init()
{
        add_action("do_canwu", "canwu");
}


int do_canwu()
{
        object ob;
        int c_skill;

        ob = this_player();

        c_skill = (int)ob->query_skill("lunhui-jian", 1);     

        if (ob->query("can_perform/lunhui-jian/xiuluodao"))
        {
                write("���Ѿ�����͸�����޵���\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("��δ��ǰ�����޷���͸���޵���\n");
                return 1; 
        } */

        if (c_skill < 500)
        {
                write("������Ҫ��ټ��ֻؽ������ܲ�͸���޵���\n");
                return 1; 
        }

        if (ob->query("jing") < 80)
        {
                write("�㾫�����ܼ��У������޷�����\n",ob);
                return 1; 
        }
      
        if (random(15) != 1)
        {
        
                write("��������˼���ã������޷���͸����֮����\n", ob);              
                return 1;
        }
		
		if (random(4) == 1)
		{
        message_sort(HIW"\n$N" HIW"������˼����Ȼ��һ����̾����"
                     "�ෲ��������ӿ����ͷ��$N" HIW "���ڽ������޵���"
                     "����������Ӵ��������ǡ�\n", ob);       
    
          write(HIC "��ѧ���ˡ����޵�����\n" NOR);
          ob->set("can_perform/lunhui-jian/xiuluodao", 1);
		}
		else 
		{
		 message_sort(HIR"\n$Nֻ�����������Σ��������⣬��Ѫ��ӿ��һͷ�Ե��ڵ�!\n", ob);    
		 ob->die();
		 return 1;
		}
		
        ob->receive_damage("jing", 75);
        ob->start_busy(2);
        return 1;
}