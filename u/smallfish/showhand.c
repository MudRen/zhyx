inherit "/inherit/room/showhand";

void create()
{
    set("short", "�������");
        set("long", @LONG
���ﲼ�õ�ʮ�ֺ������ɣ�����һ�ſ�����������������һ
��ո�µ�ֽ�ơ������ǿ�����Ƥľ�Ρ�һ�����ɵĻ��վ������
�����ơ�ǽ�Ϲ��ż򵥵Ĺ���(ruler)��
LONG
        );
    set("no_learn",1);
    set("no_fight",1);
        set("exits", ([
        "south" : __DIR__"duchang-she",
]));
    set("item_desc",([
        "pai":(:look_pai:),
        "ruler":"\n��������(sit)��ʼ,������˾��뿪(leave)\n"
"����˵����Ѻ(ya)����������(gen)����Ѻ(buya)��������\n"
"�������һ�ƿ���ȫ��(showhand)��������help suoha\n\n",
    ]));

        setup();
}

void init()
{
    object me=this_player();
    if(me->query_temp("duchang_chouma")&&!me->query_temp("duchang_gold"))
        me->delete_temp("duchang_chouma");
    add_action("do_yazhu","ya");
    add_action("do_gen","gen");
    add_action("do_buya","buya");
    add_action("do_sit","sit");
    add_action("do_leave","leave");
    add_action("do_quansuo","showhand");
    add_action("check_chouma","chakan");
}
