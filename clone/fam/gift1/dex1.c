#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + HIC "���ٸ�" NOR, ({ "fushou gao", "fushou", "gao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "����һ���������µĸ�㣬��˵���˿�����ǿ����\n" NOR);
                set("base_unit", "��");
                set("base_value", 2);
                set("base_weight", 0);
                             set("no_get", 1); 
                      set("no_put", 1); 
                      set("no_drop", 1); 
                      set("no_beg", 1); 
                                      set("only_do_effect", 1);
                set("gift_type", "dex");
                set("gift_name", "������");
                set("gift_point", 40);
                set("gift_msg", HIW "ͻȻ��ֻ��ȫ����ƮƮ�ģ��й����Ƽ���ĸо���\n" NOR);
        }
        setup();
}

