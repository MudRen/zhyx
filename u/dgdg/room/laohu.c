#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + YEL "�ϻ�" NOR, ({ "lao hu", "lao", "hu" }));
	set("long", YEL "����һֻ����ͻ������ͼ��ˡ�\n" NOR);

	set("age", 3);
	set("str", 35);
	set("dex", 50);
	set("max_qi", 9000);
	set("max_jing", 3000);
        set("neili", 25000);
        set("max_neili", 25000);
	set("combat_exp", 200000);
	set("jiali",1000);

        set("power", 40);
        set("item1", __DIR__"item/hurou");
        set("item2", __DIR__"item/hupi");


        set_skill("force",600);
        set_skill("xuanming-shengong",600);
        set_skill("xuanming-zhang",600);
        set_skill("strike",600);
        set_skill("dodge",600);
        set_skill("shexing-lifan",600);
        set_skill("parry",600);
        set_skill("jinzhong-zhao",600);
        map_skill("force","xuanming-shengong");
        map_skill("dodge","shexing-lifan");
        map_skill("parry","jinzhong-zhao");
        map_skill("strike","xuanming-zhang");
        prepare_skill("strike","xuanming-zhang");
        

        set_temp("apply/parry", 18000);
        set_temp("apply/dodge", 18000);
        set_temp("apply/attack", 18000);
        set_temp("apply/defense", 18000);
        set_temp("apply/unarmed_damage", 2200);
        set_temp("apply/armor", 2200);

	setup();
}
