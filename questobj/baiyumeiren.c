#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(WHT"��������"NOR, ({ "yumeiren" }) );
    set_weight(50);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "stone");
            set("long", WHT"һ�����ֵ�ɣ���Ө������İ������ˣ������·�������ӣ���ʳ\n�˼��̻𣬵�˧��������Ϊ�������������أ���������ͬ������\n�峺��һ����ˮ��̤�¾��ǣ������������ض���\n"NOR);
                set("skill", ([
                        "name":         "charm",
                        "exp_required": 100000,
                        "sen_cost":     100,
                        "difficulty":   100,
                        "max_skill":    50
                        ]) );
          } 
    ::init_item();
}       
