// Updated by Lonely

#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

mapping exits_name=([
	"east":            "����",
	"south":           "�Ϸ�",
	"west":            "����",
	"north":           "����",
	"eastup":          "���Ϸ�",
	"southup":         "���Ϸ�",
	"westup":          "���Ϸ�",
	"northup":         "���Ϸ�",
	"eastdown":        "���·�",
	"southdown":       "���·�",
	"westdown":        "���·�",
	"northdown":       "���·�",
	"northeast":       "������",
	"northwest":       "������",
	"southeast":       "���Ϸ�",
	"southwest":       "���Ϸ�",
	"up":              "�Ϸ�",
	"down":            "�·�",
	"enter":           "���",
	"out":             "���",
]);

int do_shoot(string id, object me, object bow, object room, string what, int m);
string exits_reverse(string dir);

string exits_reverse(string dir)
{
 	if (dir == "east") return "west";
 	if (dir == "west") return "east";
 	if (dir == "south") return "north";
 	if (dir == "north") return "south";
 	if (dir == "eastup") return "westdown";
 	if (dir == "westup") return "eastdown";
 	if (dir == "southup") return "northdown";
 	if (dir== "northup") return "southdown";
 	if (dir == "eastdown") return "westup";
 	if (dir == "westdown") return "eastup";
 	if (dir == "southdown") return "northup";
 	if (dir == "northdown") return "southup";
 	if (dir == "northeast") return "southwest";
 	if (dir == "northwest") return "southeast";
 	if (dir == "southwest") return "northeast";
 	if (dir == "southeast") return "northwest";
 	if (dir == "up") return "down";
 	if (dir == "down") return "up";
 	if (dir == "enter") return "out";
 	if (dir == "out") return "enter";

 	return "";
}

void create()
{
        set_name(HIW"����С��"NOR,({ "silver bow","bow","gong" }) );
        set_weight(14000);
        if(clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ�����Ƶľ���С����\n");
                set("unit", "��");
                set("value", 30000);
                set("consistence", 60);
                set("dam", 800);       
                set("no_put", 1);
                set("is_bow", 1);
                set("wield_msg", HIY"$N��$n"HIY"�Ӽ���ȡ�£��������С�\n"NOR);
                set("unwield_msg", HIY"$N��$n"HIY"��磬���ڼ��ϡ�\n"NOR);
                set("material", "iron");
        }
        init_hammer(10);
}

void init()
{
        add_action("do_she", "she");
}

int do_she(string arg)
{
    object me = this_player(), bow, ob, room;
   	int i, n, m;
   	string what;
   	mapping exits;
   
    room = environment(me);
   	bow = me->query_temp("weapon");

    if (room->query("no_fight"))
   		return notify_fail("���ﲻ��ս����\n");

   	if (! bow || ! bow->query("is_bow"))  
   		return notify_fail("�����ڱ����أ���ô��ѽ��\n");

   	if (me->query_str() < bow->query("dam") / 20)
   		return notify_fail("��ʹ�����̵�����Ҳ��������������������������\n");  

   	if (bow->query("consistence") < 0)
   	{
    		message_vision(HIW"$N���е�" + bow->query("name") + HIW"���ԡ���һ�����ˣ�\n", me);
    		bow->unequip();
    		destruct(bow);
    		return 1;
   	}

   	if (me->is_busy())
   		return notify_fail("��������æ���أ�\n");

   	if (me->query("qi") < 200 || me->query("jing") < 100)
   		return notify_fail("�����ھ���������ӯ��Ӳ��������Σ�հ���\n"); 

   	if (! arg || sscanf(arg, "%s %d", what, n) != 2)
   		return notify_fail("������������˼ҽ̽���ɣ�\n");
   		
    	if (n > bow->query("dam") / 200 ) n = bow->query("dam") / 200;
    	
    	for (i = 0; i < n; i++)
     	{
            if (objectp(room) && mapp(exits = room->query("exits")) && stringp(exits[what]))
      		{
       			m = i + 1;
                room = find_object(exits[what]);
      		}

	}

        if (room == environment(me))
      		return notify_fail("������㣬��������ѽ�㣿\n");
      		
        if (objectp(room))
     	{
            if (room->query("have_quest") || room->query("no_fight"))
      			return notify_fail("�������������ӣ����������Ҳ��\n"); 
      			
            "/cmds/std/look.c"->look_room(me, room);  
      		
      		message_vision(HIY"$N�Ӽ����ڳ��һ֧"HIW"���"HIY"������"
       				+ bow->query("name") + HIY"�ϣ��������һ�������Ϲ�ʽ��\n��"HIR
       				+ exits_name[what] + HIY"�ѹ�����.......\n"NOR, me);
       				
            tell_object(all_inventory(room), HIB"�����һ�����ҵ�ɱ����"HIR
       				+ exits_name[exits_reverse(what)] + HIB"��������\n"NOR);

      		tell_object(me, HIR + exits_name[what] + HIW"���龰��һĿ��Ȼ��"
                                + "�������������׼�ˡ���>\n"NOR);   
      		me->start_busy(2 + random(3));  
            input_to("do_shoot", me, bow, room, what, m);
     	} else return notify_fail("������㣬��������ѽ�㣿\n");  

    	return 1;
}


int do_shoot(string id, object me, object bow, object room, string what, int m)
{
    	object ob, obj, *env;
    	int damage, ratio;

    	if (! id || id == "") 
    	{
     		message_vision("$N̾�˿�����������" + bow->query("name") + "����ȡ��������\n", me);
     		return 1;
    	}

    	if (objectp(ob = present(id, room)) && ob->is_character())
    	{
     		if (ob->query("is_quest") && ob->query("killer") != me->query("id"))
     		{
      			tell_object(me, "���顱��һ�����㱻" + bow->query("name")
                                  	+ "����һ�£�����Ŀ�겻����ѽ��\n");
      			return 1;
     		}

     		if (playerp(ob) && ob->query("age") < 18)
     		{
      			tell_object(me, "���顱��һ�����㱻" + bow->query("name")
                                  	+ "����һ�£�ԭ�����Ŀ����С����ѽ��\n");
      			return 1;
     		}

      		message_vision(HIY"$N��ಡ���һ����"HIR + exits_name[what] + HIY"���˳�ȥ��\n", me);

      		damage = bow->query("dam") * (5 + me->query_str()) / (m * 5 + ob->query_dex());
      		if (damage < 100) damage = 100;
      		if (damage > 1500) damage = 1500;
      		damage = damage + random(damage);
      		
                me->want_kill(ob);

     		if (random(me->query_skill("arrow", 1)) > ob->query_skill("dodge", 1) / 4
         	||  random(me->query("combat_exp")) > ob->query("combat_exp") * 2)
     		{
      			if (damage > 2000)
        			message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"��ͷ"HIY"�ϣ�\n"NOR,
           					ob);
      			else if (damage > 1500)
        			message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"�ؿ�"HIY"�ϣ�\n"NOR,
           					ob);
      			else if (damage > 1000)
        			message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"���"HIY"�ϣ�\n"NOR,
           					ob);
      			else if (damage > 500)
        			message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"С��"HIY"�ϣ�\n"NOR,
           					ob);
      			else
        			message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           					+ exits_name[exits_reverse(what)]
           					+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"�ֱ�"HIY"�ϣ�\n"NOR,
           					ob);
      			damage = damage / 4 + random(damage / 2);       			   
      			ob->receive_damage("qi", damage, me);
      			
      			if (damage > (int)ob->query_temp("apply/armor"))
      				ob->receive_wound("qi", damage - (int)ob->query_temp("apply/armor"), me);
      			
      			COMBAT_D->report_status(ob, random(2));  
      				tell_object(me, HIR"�ٺ٣�Ŀ��Ӧ�����������Ǻü�����\n"NOR);

      			ratio = me->query("combat_exp") / 100;
      			ratio = ob->query("combat_exp") / ratio; 
      			if (ratio > 1000) ratio = 1000;
      			if (ratio < 10) ratio = 10;
      			if (! playerp(ob))
      				me->improve_skill("arrow", 
      					random((damage / 2 + me->query_int() / 10) * ratio / 100), 0);

      		} else
      		if (random(3) > 0)
      		{
       			env = all_inventory(room);
       			obj = env[random(sizeof(env))];
       			if (obj != ob && obj->is_character())
       			{
       				damage = bow->query("dam") * (5 + me->query_str()) / (m * 5 + obj->query_dex());
       				if (damage < 100) damage = 100;
       				if (damage > 1500) damage = 1500;
       				damage = damage / 2 + random(damage / 2); 

       				if (damage > 2000)
        				message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"��ͷ"HIY"�ϣ�\n"NOR,
           						obj);
       				else if (damage > 1500)
        				message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"�ؿ�"HIY"�ϣ�\n"NOR,
           						obj);
       				else if (damage > 1000)
        				message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"���"HIY"�ϣ�\n"NOR,
           						obj);
       				else if (damage > 500)
        				message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"С��"HIY"�ϣ�\n"NOR,
           						obj);
       				else
        				message_vision(HIY"��ಡ���һ����һö"HIW"�����"HIR
           						+ exits_name[exits_reverse(what)]
           						+ HIY"������"HIR"�����͡�"HIY"һ������$N"HIR"�ֱ�"HIY"�ϣ�\n"NOR,
           						obj);
        			damage = damage / 4 + random(damage / 2);
        			obj->receive_damage("qi", damage, me);
        			if (damage > (int)obj->query_temp("apply/armor"))
        				obj->receive_wound("qi", damage - (int)obj->query_temp("apply/armor"), me);
        			COMBAT_D->report_status(obj, random(2));  

        			tell_object(me,HIB"��⣬�������䵽�����ˣ��ú��������ɣ�\n"NOR);
       			} else
       			{
        			message_vision(HIY"һö"HIW"�����"HIR + exits_name[exits_reverse(what)]
           					+ HIY"������"HIR"��ಡ�"HIY"��һ����$N"HIR"����"NOR"�ɹ���\n"NOR,
           					ob);
        			tell_object(me, HIW"��ѽ��������ˣ��ú��������ɣ�\n"NOR);
       			}
      		} else
      		{
        		message_vision(HIY"һö"HIW"�����"HIR + exits_name[exits_reverse(what)]
           				+ HIY"������"HIR"��ಡ�"HIY"��һ����$N"HIR"����"NOR"�ɹ���\n"NOR,
           				ob);
        		tell_object(me,HIW"��ѽ��������ˣ��ú��������ɣ�\n"NOR);
      		}
    	} else
     		tell_object(me, "��ϧ��Ŀ�����ڲ��������ˣ���ļ�����Ү��\n");

     	bow->add("consistence", -1);
     	me->receive_damage("jing", 50, me);
     	me->receive_damage("qi", 100, me);

     	return 1;
}    

