#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW "\n\n                ��        ��        ��" NOR);
        set("long", HIW "\n"
"ãã�ƺ������ޱ߼ʡ����ܽ��ɢ�������ƶ�䣬Զ���з��\n"
"���ƣ�������Ϸ�����ߴ�����������������ãȻ��֪���롣��\n"
"�������鼰���硢ɫ�缰��ɫ�����硣�����������죬ɫ����\n"
"����ʮ���죬��ɫ�����죬���ж�ʮ���졣��������������\n"
"(canwu)��\n\n" NOR);
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

        if (ob->query("can_perform/lunhui-jian/tiandao"))
        {
                write("���Ѿ�����͸���켫����\n");
                return 1;
        }

/*         if (!ob->query("reborn"))
        {
                write("��δ��ǰ�����޷���͸�켫����\n");
                return 1; 
        }
 */
        if (c_skill < 700)
        {
                write("������Ҫ�߰ټ��ֻؽ������ܲ�͸�켫����\n");
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
		
		if (random(5) == 1)
		{
        message_sort(HIW"\n$N" HIW"������˼����Ȼ��һ����̾����"
                     "�ෲ��������ӿ����ͷ��$N" HIW "���ڽ����켫����"
                     "����������Ӵ��������ǡ�\n", ob);       
    
          write(HIC "��ѧ���ˡ��켫������\n" NOR);
          ob->set("can_perform/lunhui-jian/tiandao", 1);
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