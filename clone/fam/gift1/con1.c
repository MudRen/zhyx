#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + WHT "׳�Ƿ�" NOR, ({ "zhuanggu fen", "zhuanggu", "fen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "����һ���Һ�ɫ��ҩ�ۣ���˵���˿�����ǿ���ǡ�\n" NOR);
                set("base_unit", "��");
                set("base_value", 0);
                             set("no_get", 1); 
                      set("no_put", 1); 
                      set("no_drop", 1); 
                      set("no_beg", 1); 
                      set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "con");
                set("gift_name", "�������");
                set("gift_point", 40);
                set("gift_msg", HIM "ͻȻ��������������ͣ�����漴��ƽ����������\n" NOR);
        }
        setup();
}
