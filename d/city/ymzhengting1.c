#include <ansi.h>
inherit ROOM;
//void kf_same(object who,object me);

void create()
{
        set("short", "��������");
        set("long", "
    ���϶����������ס������һ������������������ϸ������ǽ������һ����
�ң������ĸ���������Ĵ��֡�֪���������İ����������飬ʦү�����ں�
�������и���һ�ң�\n"HIR+"
               ��    ��    ��    ��\n\n"NOR
        );
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_magic", "1");
        set("no_fight", "1");
        set("exits", ([
           "east"  : __DIR__"dongting", 
                      "west"  : __DIR__"xiting", 
                      "north" : __DIR__"neizhai", 
                      "south" : __DIR__"yamen", 

        ]));
  

        set("objects", ([
                  __DIR__"npc/cheng" : 1, 
                  __DIR__"npc/shiye" : 1, 
        ]));
        setup();
}

void init ()
{
        add_action("do_work","work");
        add_action("do_finish","finish");
}

int do_work (string arg)
{
        object ob,ob1;
        int kf_npc,kf_whatnpc,worked_num;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        if ((int)me->query("kf_jiangli"))
                return notify_fail("��ҩ��˵�����񲶴��˻�û������ʥ����\n");

        if (!(int)me->query("kaifengfu"))
                return notify_fail("�������۴����ȵ����󵨵��񣬲����������ã�\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("��������Ц������ҩ���Ѿ������ˣ�Ҫ��������������������\n");

        if (present("ling pai",me)||(int)me->query("kf_working"))
                return notify_fail("��ҩ����ɫһ����������ǰ�ս�����Ĳ�����ȥ���������������أ�\n");
        kf_npc = 1 + random(209);
        kf_whatnpc =1+random(8);
        me->set("kf_whatnpc",kf_whatnpc);
        ob = new(__DIR__"obj/lingpai");        //50
        if(kf_whatnpc==1){ob1 = new(__DIR__"npc/tufei1");}
        if(kf_whatnpc==2){ob1 = new(__DIR__"npc/tufei2");}
        if(kf_whatnpc==3){ob1 = new(__DIR__"npc/tufei3");}
        if(kf_whatnpc==4){ob1 = new(__DIR__"npc/tufei4");}
        if(kf_whatnpc==5){ob1 = new(__DIR__"npc/tufei5");}
        if(kf_whatnpc==6){ob1 = new(__DIR__"npc/tufei6");}
        if(kf_whatnpc==7){ob1 = new(__DIR__"npc/tufei7");}
        if(kf_whatnpc==8){ob1 = new(__DIR__"npc/tufei8");}
        ob ->move(me);
        me->set_temp("kf_npc",kf_npc);
        if(kf_npc<210) kf_where = "�䵱����";
        if(kf_npc<191) kf_where = "��ɽ����";
        if(kf_npc<166) kf_where = "��ң�ɸ���";
        if(kf_npc<152) kf_where = "�����ɸ���";
        if(kf_npc<141) kf_where = "̩ɽ����";
        if(kf_npc<125) kf_where = "ѩɽ����";
        if(kf_npc<107) kf_where = "���ݸ���";
        if(kf_npc<84) kf_where = "��������";
        if(kf_whatnpc==1){ kf_name = "������"; kf_name1 = "��·����,ɱ������";}
        if(kf_whatnpc==2){ kf_name = "��Ӱ��͵"; kf_name1 = "�Ĵ����Բ���";}
        if(kf_whatnpc==3){ kf_name = "���������"; kf_name1 = "����������Ů���޶���";}
        if(kf_whatnpc==4){ kf_name = "ħ��ϸ��"; kf_name1 = "�Ĵ��";}
        if(kf_whatnpc==5){ kf_name = "���ڼ�ϸ"; kf_name1 = "�Ĵ���ҥ�ƻ�";}
        if(kf_whatnpc==6){ kf_name = "������"; kf_name1 = "��ɱ��͢����";}
        if(kf_whatnpc==7){ kf_name = "��Ԫ��"; kf_name1 = "��ҽ���";}
        if(kf_whatnpc==8){ kf_name = "����"; kf_name1 = "��������";}

        me->set_temp("kf_whatnpc",kf_whatnpc);
        me->set_temp("kf_name",kf_name);
        me->set_temp("kf_where",kf_where);
        message_vision ("��ҩ��һ�ľ���ľŭ�����ݲ����"+kf_name+"��"+kf_where+kf_name1+"��"+me->query("name")+"��ȥ�ư�����������\n",me);
        me->set("kf_working",1);
        return 1;
}
int do_finish (string arg)
{
        object ob;
        int kf_npc,kf_whatnpc,kf_exp,kf_qn;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        ob= present("ling pai",me);
        kf_name = me->query_temp("kf_name");
        kf_where = me->query_temp("kf_where");
        
        if (!(int)me->query("kaifengfu"))
                return notify_fail("���Եķ������۴����ȵ����󵨵��񣬲����������ã�\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("��������Ц�����̴����Ѿ������ˣ�Ҫ�뽻����������������\n");
        if (!me->query("kf_working"))
                return notify_fail("��ҩ����ɫһ����������ʲôʱ���ɹ�����°���\n");
        if (!(int)me->query_temp("kf_finish"))
                return notify_fail("��ҩ����ɫһ��������������Ĳ�ʹ����δ���ף��㻹����Ŀ�����ң�\n");
        if (present("ling pai",me)){
                tell_object(me, "�㹧�������Ľ������ơ�\n" NOR );
        destruct(present("ling pai",me));
        }        
        message_vision (WHT"��ҩ��΢΢һЦ����"+me->query("name")+WHT"��"+kf_where+WHT"�ƻ�"+kf_name+WHT"һ�����Ϳ๦�ߣ��Ͽ���ȥ��Ϣ�ɣ�\n"NOR,me);
        kf_exp = 2000+random(2000);
        kf_qn = 500+random(500);
        me->add("combat_exp",kf_exp);
        me->add("kf_worked",1);
        me->add("potential",kf_qn);
        me->add("kf_worked",1);
        me->set("kf_working",0);
        me->delete_temp("kf_finish");
        tell_object(me, "������" + chinese_number(kf_exp)+ "�㾭�顣\n" NOR );
        tell_object(me, "������" + chinese_number(kf_qn)+ "��Ǳ�ܡ�\n" NOR );
        if (me->query("kf_worked")==4800){
                me->set("kainame",10);
                me->add("shen",3000);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
                message_vision (WHT"��ҩ��΢Ц��˵����"+me->query("name")+"���ƴ󰸣����������������Ѿ��������ϡ�\n���ճ�ּ���£�����ƽ���ǧ��������Ե�Ǯׯ��ȡ��"NOR,me);
                 me->add("balance",10000000);
               me->set("kf_jiangli",1);

      }
        if (me->query("kf_worked")==3200){
                me->add("shen",3000);
                me->set("kainame",9);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
                message_vision (WHT"��ҩ��΢Ц��˵����"+me->query("name")+"���ƴ󰸣���������,�������ͣ���"NOR,me);
      }
        if (me->query("kf_worked")==1600){
                me->set("kainame",8);
                me->add("shen",1500);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
      }
        if (me->query("kf_worked")==800){
                me->set("kainame",7);
                me->add("shen",1000);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
        }
        if (me->query("kf_worked")==400){
                me->set("kainame",6);
                me->add("shen",800);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
        }
        if (me->query("kf_worked")==200){
                me->set("kainame",5);
                me->add("shen",400);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
        }
        if (me->query("kf_worked")==100){
                me->set("kainame",4);
                me->add("shen",200);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
        }
        if (me->query("kf_worked")==50){
                me->set("kainame",3);
                me->add("shen",100);
                message_vision(HIC "$N����������ˣ�\n" NOR,me);
                tell_object(me, "�����ڵ�������" + chinese_number((string)(me->query("shen")))+"��\n"NOR);
        }
        if (me->query("kf_worked")==20){
                me->set("kainame",2);
        }
        me->save();
        return 1;
}
int valid_leave (object who, string dir)
{
        if(who->query_condition("kf_stop")<1){
                return ::valid_leave(who, dir);
        }
        else{
                message_vision ("$N���������������ܡ�\n",who);
                return notify_fail(WHT"�����������㰴�ڵ��Ϻȵ�����ʵ�㣡\n"NOR);
                return 1;
}
}

