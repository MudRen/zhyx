// Ů���

#include <ansi.h>
inherit ITEM;

#define QINGTIAN    "/u/sanben/special/xuannv/xuanyin.h"
#define XUANNVJIAN       "/u/sanben/special/xuannv/xuannvjian.h"
#define SPECIAL     "/data/item/special/"

void create()
{
        set_name(HIW "Ů���" NOR, ({ "statue"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "��Ů洵���һ��ׯ�ϱ��࣬��ʱ���㾴"
                               "η֮����Ȼ�������������ӡ�\n" NOR);
                set("unit", "��");                
                set("no_sell",1);
                set("weight", 10000);
                set("no_get",1);                
             }
        setup();
}
