// �Ϲ�ʮ������֮ ����ʯ 
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

//int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "����ʯ" NOR, ({ "zhenlong shi", "zhenlong", "shi" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", NOR + YEL "����һ�鷺���߲ʹ�â��ʯͷ����˵��ʯ�˻Ƶ۵Ļ������\n"
                                      "ֻҪ�������������󲻻ᶪʧ���飬Ǳ���Լ����ܡ�\n"
                                      "���������ߺ󲻶�ʧ�����ʯͷ������Գ�(chi)��ȥҮ��\n" NOR);

        }
        setup();
}



void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
}


int do_eat(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (me->is_fighting())
                return notify_fail("ս�����޷��ж���\n");

        if (arg && id(arg))
        {
                if (me->query("skybook/guard/death") >= 1)
                  // || me->query("combat_exp") > 2500000)
                        return notify_fail(HIW "\n�������ܵ�������˵ı����أ������´��ٳ԰�n" NOR);
          if (random(5)!=1) 
          	{
                log_file("static/using", sprintf("%s(%s) use ����ʯ at %s.\n",
                                                 me->name(1), me->query("id"),
                                                 ctime(time())));

                message_vision(HIY "$N" HIY "ƴ����ҧ" + query("name") + HIY"ͻȻ����һ��,"+query("name")+HIY"��ҧ���ˣ���ʱ��һ���⻪����$P" HIY "�����ӡ�\n" NOR, me);

                tell_object(me, HIC "ڤڤ�����ƺ��ܵ���ĳ�ֵ����ϣ����յ�һ�з�"
                                "�ս������Ŵ�����\n" NOR);

                me->add("skybook/guard/death", 1);
                me->start_busy(1);
                destruct(this_object());
                return 1;
              }
           else 
           	{
           		
           		tell_object(me, HIW "\n��а��а����Ѵ�����������ˣ�����û�Ȱ�ʯͷ����ȥ��ȴ�����������ʯ�л��ˣ�Ӵ�������ˣ�\n" NOR);
           		destruct(this_object());  
           		return 1;
              }
           
        }
}


int query_autoload()
{
	return 1;
}