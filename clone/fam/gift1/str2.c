#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIW "�׻���Ԫ��" NOR, ({ "baihu dan", "baihu", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "����һ�Ŵ�����Ͼ��ҩ�裬��˵���˿�����ǿ������\n" NOR);
                set("base_unit", "��");
                set("base_value", 0);
                set("base_weight", 50);
             set("no_get", 1); 
                      set("no_put", 1); 
                      set("no_drop", 1); 
                      set("no_beg", 1); 
                       set("only_do_effect", 1);
                set("gift_type", "str");
                set("gift_name", "��������");
                set("gift_point", 65);
                set("gift_msg", HIY "ͻȻ����ֻ��˫�ۼ������ѣ�������������\n" NOR);
        }
        setup();
}

