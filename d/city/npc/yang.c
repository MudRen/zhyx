
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("������", ({ "yang yongfu", "yang", "yongfu" }));
        set("title", "�ӻ����ϰ�");
        set("shen_type", 1);
        set("gender", "����");
        set("age", 45);
        set("long", "���ϰ������������������ˣ����˼�ʮ���С������\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/clone/cloth/cuttonp",
                __DIR__"obj/mabudai",
                   "/d/wudu/obj/huoba",
                __DIR__"obj/beixin",
                __DIR__"obj/toukui",
                __DIR__"obj/cycle",
                __DIR__"obj/surcoat",
                __DIR__"obj/shield",
                __DIR__"obj/huwan",
                __DIR__"obj/zhitao",
                __DIR__"obj/huyao",
                __DIR__"obj/caoxie",
                __DIR__"obj/pixue",
                __DIR__"obj/shoutao",
                __DIR__"obj/tieshou",
                __DIR__"obj/jinsijia",
				"/d/city/obj/bathwater",
                "/d/xingxiu/obj/fire",
                "/d/taohua/obj/bagua",
                "/d/item/obj/chanhs",
                "/clone/misc/wood",
                "/clone/misc/shoeshine",
                "/clone/misc/brush",
                "/d/room/obj/paper",    
				"/clone/book/chess-book",    
                "/clone/misc/sleepbag",           
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
