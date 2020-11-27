// longwen-pei.c ���ƫ�
// By Alf, Last Update 2002.03

#include <ansi.h>
#include <armor.h>

inherit WAIST;
int do_ding(string arg);

string query_autoload()
{
	return 1 + "";
}

void create()
{
	set_name(HIG"���ƫ�"NOR, ({"fengwen pei"}));
	set_weight(500);
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit","��");
		set("long",
"\n�������񫘴���ս����͢������Ϊ�ԣ�Ԣ���\n"
"�飬������Ů��֮��Ϊ"HIM"����"NOR"���һ�����Ƿ�\n"
"�ƫ���ɫ��Ө�̣��������£�һ�����������\n"
"���ķ��ƣ���һ����������С�֣�\n"
HIG"\n\t�����\n"
"\tǿ������\n"
"\tǫǫ����\n"
"\t��������\n\n"NOR);
		set("value",50000);
		set("armor_prop/armor",25);
		set("armor_prop/personality",20);
		set("wear_msg","$N��һ��$n����������䡣\n");
		set("unequip_msg","$N�����������$n����������\n");
		set("huang",1);
	    set("no_put",1);
	    set("no_get",1);
	    set("no_drop",1);
	    set("no_steal",1);
	    set("no_leave",1);
	}
	setup();
}

void init()
{
	add_action("do_ding","����");
}

int do_ding(string arg)
{
	object me,who,ob,ob1;
	string arg1;
	me=this_player();
	ob=this_object();
	if (!arg) 
               return notify_fail("��Ҫ��˭���飿\n");

	if (! objectp(who = present(arg, environment(me))) || !userp(who))
               return notify_fail("����û��"+ arg + "�����ҡ�\n");

       if (!objectp(ob1 = present("longwen pei",me)))
               return notify_fail("����˫���ǳɶԵģ���ֻ�з����壬��ô�������飿\n");

       if (me->query("gender") == "����")
		return notify_fail("��һ��̫�࣬Ҳ������˶��飿\n");

       if (who->query("gender") == "����")
		return notify_fail("��û�и��" + who->name() + "����һ��̫�࣬��Ҳ�붨�飿\n");

       if (who->query("gender") == me->query("gender"))
              return notify_fail("����ʲô��������ͬ����Ҳ�����ˣ��������ô��������ĸ�ɶ��\n");

       if (who->query("gender") == "Ů��")
       {
              ob->move(who);
              message_vision("$N����Ķ�$n˵��������ĺ�ϲ���㣬������������ҵ��ģ������°ɡ�\n",me,who);
              message_vision("$N��һ��Ө�̵�����ݸ�$n��\n",me,who);
              tell_object(who,"��ֻ��������һ����ů��ȴ�����������һ��Ө�̵����壬�������������ķ��ͼ��\n");
        } else
        {
              ob1->move(who);
              message_vision("$N����Ķ�$n˵��������ĺ�ϲ���㣬�������������ҵ��ģ������°ɡ�\n",me,who);
              message_vision("$N��һ��Ө�̵�����ݸ�$n��\n",me,who);
              tell_object(who,"��ֻ��������һ����ů��ȴ�����������һ��Ө�̵����壬������������������ͼ��\n");
        }
        return 1;
}
