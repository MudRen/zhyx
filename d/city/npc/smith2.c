// smith.c

#include <ansi.h>

inherit "/inherit/char/b_npc.c";    

mixed ask_back();

void create()
{
        set_name("���ϰ�", ({ "tie boss", "tie", "boss" }));
         set("title", "�����̺�̨�ϰ�");
	 set("shen_type", 1);

        set("gender", "����" );
        set("age", 33);
        set("long", "�����������̵������ϰ塣\n");

        set("combat_exp", 400);
	 set("attitude", "friendly");
        set("vendor_goods",({
                "/clone/weapon/changjian",
                "/clone/weapon/hammer",
                "/clone/weapon/tudao",
		  "/clone/weapon/dagger",
                "/clone/weapon/tiegun",
                "/clone/weapon/changbian",
                "/clone/weapon/gangdao",
                "/clone/cloth/tiejia",
                "/d/item/obj/jingtie",
                "/clone/weapon/arrow",
                "/clone/weapon/wolfarrow",
                "/clone/weapon/bow",
                "/clone/weapon/longbow",
                "/clone/weapon/qimeigun",
        }));

        set("inquiry", ([
//                "����" : (: ask_me :),
//                "job"  : (: ask_me :),
//                "Ѫ���ޱ�" : (: ask_back :),
        ]));

	setup();

	carry_object("/clone/misc/cloth")->wear();
}






