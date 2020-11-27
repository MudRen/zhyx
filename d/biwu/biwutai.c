// ɽè(adx) by snow 2000-05-15

#include <ansi.h>
inherit ROOM;

string look_shelf();

void create ()
{
        set ("short", "����̨");
        set("long", @LONG
����һ�����ɼ�������̨����׳��ʵ��ľ������һƬƽ̨���Ľǵ�֧����
�߹����ĸ�����������Ĺ��ڶ�������ؿ���̨�ϵ�������䡣��̨�����и�
������(shelf) �������ް�������ȫ������̨�����ǹ��ϯ��
LONG );
        set("info_sends",1);
        set("biwutai",1);
        set("exits", ([
                "north"   : __DIR__"caipan",
                "down"   : __DIR__"kantai2",
        ]));
set("item_desc", ([
                "shelf" : (: look_shelf :),
        ]));


        set("no_openshelf", 1);

        setup();
}

void init()
{
        add_action ("do_fight","fight");
        add_action ("do_fight","kill");
        add_action ("do_fight","hit");
        add_action ("do_work","quit");
        add_action ("do_work","halt");
        add_action("do_take","take");
        add_action("do_open","open");
        add_action("do_close","close");

}

int do_fight(string arg)
{
        object me=this_player();
        object *inv=all_inventory(environment(me));
        object ob;
        object who;
        int i;

        if(!arg) { 
                write("��Ҫͬ˭���䣿\n");
                return 1;
        }
        ob=present(arg, environment(me));
        if(!ob) {
                write("����û������ˣ�\n");
                return 1;
        }
        if(ob==me) {
                write("��Ҫͬ�Լ����䣿����\n");
                return 1;
        }
        if(!interactive(ob)) {
                write("�������޷�ͬ����䣡\n");
                return 1;
        }
        if(!userp(me) || !userp(ob)) {
                write("�������޷�ͬ����䣡\n");
                return 1;
        }

        for(i=0; i<sizeof(inv); i++) {
                who=inv[i];
                if(who->is_fighting()) {
                        write("̨��"+who->query("name")+"�����ڱ��䣬���Ժ\n");
                        return 1;
                }
        }

        message("channel:chat",HIW"�����䳡��"+
                me->query("family/family_name")+"��"+me->query("name")+"��"+
                ob->query("family/family_name")+"��"+ob->query("name")+
                "�ڱ���̨�Ͻ����ߵͣ�\n\n"NOR,users());

        me->set("biwu_fighter",1);
        ob->set("biwu_fighter",1);

	me->set_temp("last_opponent",ob);
	ob->set_temp("last_opponent",me);

        me->kill_ob(ob);
        ob->kill_ob(me);
        return 1;
}

void info_sends(string str)
{
        tell_room(__DIR__"kantai1", str);
        tell_room(__DIR__"kantai2", str);
        tell_room(__DIR__"kantai3", str);
}

int no_die(object me)
{
        object ob,obj,where;
	string id,id1;
	ob = me->query_temp("last_opponent");
	if (! ob)
		{
			message_vision (HIC"$N�͵ط���ʮ�˸�¿�������������̨��\n"NOR,me);
			me->revive();
			me->move(__DIR__"kantai1");
			me->set("eff_qi",me->query("max_qi")); 
			me->set("eff_jing",me->query("max_jing"));               
			me->add("qi",10);
			me->add("jing",10); 
			me->clear_condition();
			return 1;
		}
	
	id=ob->query("id");
	id1=me->query("id");

        me->delete_temp("last_opponent");
        ob->delete_temp("last_opponent");
        me->remove_all_killer();
        ob->remove_all_killer();
	me->clear_condition();
	ob->clear_condition();

        me->set("eff_qi",me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        me->set("eff_jing",me->query("max_jing"));  
        me->set("jing", me->query("max_jing"));
        me->set("jingli", me->query("max_jingli"));
        me->set("neili", me->query("max_neili"));
	me->revive();

        ob->set("eff_qi", ob->query("max_qi"));
        ob->set("qi", ob->query("max_qi"));
        ob->set("eff_jing", ob->query("max_jing"));
        ob->set("jing", ob->query("max_jing"));
	ob->set("jingli", ob->query("max_jingli"));
        ob->set("neili", ob->query("max_neili"));

        message("channel:chat",HIW"�����䳡��"+
                ob->query("family/family_name")+"��"+ob->query("name")+"�ڱ���̨����"+
                me->query("family/family_name")+"��"+me->query("name")+"��\n\n"NOR,users());

        message_vision (CYN"$N���ص�ˤ�ڵ��ϣ�\n"NOR,me);
        message_vision (CYN"\n$N�����ӵ���������������׳���������±���̨��\n"NOR,me);
        me->move(__DIR__"kantai1");
        message_vision (CYN"$N��׳�������������˹�����\n"NOR,me);
        message_vision (CYN"����׳�������Ŵ�ӵ��$N���±���̨��\n"NOR,ob);
        ob->move(__DIR__"kantai3");
        message_vision (CYN"$N������׳����ӵ�����˹�����\n"NOR,ob);

        me->delete("biwu_fighter");
        ob->delete("biwu_fighter");

        if (!where=find_object(__DIR__"gate"))
                where=load_object(__DIR__"gate");
        obj=present("gongping zi", where);
        if(obj->query("fangshi")!="������") {
                if(obj->query("start/juesai"))
                        obj->jieshu_biwu(id, id1);
                        obj->keep_biwu(id);
        }
        return 1;
}

string look_shelf()
{
        return 
"\n
�����������ǧ���ľ������һ���ı����ܣ�ɫ�����ޣ�ʮ�ֻ�����
���ϰ�����: 
                 �ֵ�(blade)    ����(sword)
                 ����(staff)    ����(whip)
                 ����(hammer)   ����(club)
                 ����(throwing) �̱�(dagger)
                 �ּ�(armor)

�μӱ����߿��԰���Ҫ�������ȡ(take)ʹ�á�

                                     ��ʦ��  ���� 
\n";
}

int do_open()
{
        if(wizardp(this_player()))
        {
                message_vision("$N�ѱ����������ˡ�\n", this_player());
                this_object()->delete("no_openshelf");
                return 1;
        }
        else return 0;
}
int do_close()
{
        if(wizardp(this_player()))
        {
                message_vision("$N�����������ѱ����ܸ����ˡ�\n", this_player());
                this_object()->set("no_openshelf", 1);
                return 1;
        }
        else return 0;
}

int do_work()
{
        write("���ﲻ��ʹ�����ָ�\n");
        return 1;
}
int do_take(string arg)
{
        object obj,ob;
        ob = this_player();
        if(this_object()->query("no_openshelf"))
        {
                message_vision("�Ǵ�����ʱ�򣬱����ܸ���ס�ˡ�\n", ob);
                return 1;
        }
        if( !arg || arg=="" )
        {
                message_vision("$Nվ�ڱ�����ǰ����û���Ҫʲô������\n", ob);
                return 1;
        }
        switch (arg)
        {
                case "sword":
                        obj = new("/clone/weapon/changjian");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ�ڳ�����\n",ob);
                        break;
                case "blade":
                        obj = new("/clone/weapon/gangdao");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ�ڸֵ���\n",ob);
                        break;
                case "staff":
                        obj = new("/clone/weapon/gangzhang");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ�˸��ȡ�\n",ob);
                        break;
                case "whip":
                        obj = new("/clone/weapon/changbian");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ�����ޡ�\n",ob);
                        break;
                case "club":
                        obj = new("/clone/weapon/qimeigun");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ����ü����\n",ob);
                        break;
                case "hammer":
                        obj = new("/clone/weapon/hammer");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ��������\n",ob);
                        break;
                case "throwing":
                        obj = new("/clone/weapon/lianzi");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ�������ӡ�\n",ob);
                        break;
                case "dagger":
                        obj = new("/clone/weapon/dagger");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ��ذ�ס�\n",ob);
                        break;
                case "armor":
                        obj = new("/clone/weapon/tiejia");
                        obj -> move(ob);
                        message_vision("$N�ӱ�������ȡ��һ�����ס�\n",ob);
                        break;
                default:
                        message_vision("$Nվ�ڱ�����ǰ����û���Ҫʲô������\n", ob);
        }
        return 1;
}

int valid_leave(object me, string dir)
{
        if ( !wizardp(me) && dir=="north" ) {
                return notify_fail("�㼴�����������ʦҲ����������ʦ���ܵ����ϯ��\n");
        }

        if ( !wizardp(me) && dir=="down" ) {
                if( me->query("biwu_fighter") )
                        return notify_fail("������Ҫ�����ˣ���Ҫ�������ܡ�\n");
        }

        me->delete_temp("last_opponent");
        me->delete_temp("last_damage_from");
        me->remove_all_killer();

        return ::valid_leave(me, dir);
}


