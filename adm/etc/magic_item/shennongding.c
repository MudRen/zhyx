// �Ϲ�ʮ������֮ ��ũ��
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

// ���Ƶĵ�ҩ
string *gifts = ({
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
        "/clone/fam/gift/int3",
        "/clone/fam/gift/con3",
        "/clone/fam/gift/str3",                        
        "/clone/fam/gift/dex3",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
        "/clone/fam/gift/int4",
        "/clone/fam/gift/con4",
        "/clone/fam/gift/str4",
        "/clone/fam/gift/dex4",                                                
        "/clone/fam/max/naobaijin",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",
        "/clone/fam/pill/yulu",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
});

void create()
{
        set_name(HIG "��ũ��" NOR, ({ "shennong ding", "shennong", "ding" }) );
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIG "����һ�������������õĶ�����˵�Ϲ���ũ���ٲ�����ҩ������"
                                "֮�������߾��������ũ����\n"
                                "���������������(lianzhi)������ĵ�ҩ��ʹ��liandan ? "
                                "�鿴��ʹ�ô�����\n���Ƶ�ҩ��Ҫ������һ�ټ���\n" NOR);
        }

        setup();
}

void init()
{
        add_action("do_lianzhi", "lianzhi");
}

int do_lianzhi(string arg)
{
        object me, ob;
        int i;
        string gift;

        me = this_player();
        
        if(! objectp(present("shennong ding", me)))return 0;

        if (arg == "?")
        {
        	 write(HIG "ʹ�ô��� " + this_object()->query("count") + "/5\n" NOR);
        	 return 1;
        }
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");          

        message_sort(HIG "\n$N" HIG "����ũ�����ڵ��ϣ������Խ�ȥһЩҩ�ģ������أ�������"
                         "������ð�����⻪��� ����\n" NOR, me);

        gift = gifts[random(sizeof(gifts))];
        ob = new(gift);
        if (! objectp(ob))
        {
        	write(HIR "��� " + gift + " ���Ƴ���\n" NOR);
        }
        else
        {
                write(HIG "�����Ƴ��� " + ob->name() + HIG + " ��\n" NOR);
                ob->move(me, 1);
        }
             
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 5)
        {
        	write(HIW "ֻ����һ���������������ũ�������ˡ�\n" NOR);
        	destruct(this_object());	        	
        }
        
        return 1;
}
