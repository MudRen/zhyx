// Code of ShenZhou
// Ryu, 11/20/96.
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW"����"NOR, ({ "bing can"}) );
        set("race", "����");
        set("subrace", "����");
        set("age", 3);
        set("long", "��ϳ洿������΢����ɫ����Ѱ���Ĳ϶�����һ�����࣬����һ����򾣬����͸��ֱ��ˮ����\n");
        set("attitude", "peaceful");

//        set("limbs", ({ "ͷ��", "����", "����", "ǰ��" }) );

        set("combat_exp", 900);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 6);
        set_temp("apply/armor", 1);

        set("insect_poison", ([
                "level"  : 200,
                "maximum": 80,
        ]));

        setup();
}