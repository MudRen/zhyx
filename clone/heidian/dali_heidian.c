// �ڵ�: /clone/heidian/dali_heidian.c
// �ڵ������smallfish��д

inherit ROOM;
inherit F_HEIDIAN;

void create()
{
    set("short", "�������");
    set("long", @LONG
�����Ǵ���ʦ���ǵĵ���, ���������һЩϣ��Źֵ������,
ֻҪ������û�в����⿴��,Ҳ�����ҵ��Լ�����Ķ���, ƽʱ����
Ҳ����, ֻ��һ��СŮ���ڿ���.
LONG);

    set("no_fight", 1);
    set("exits", ([/* sizeof() == 1 */
        "east":"/d/dali/center",
    ]));
    set("no_steal", 1);
    set("shop_type", 0);
    set("objects", ([/* sizeof() == 1 */
        __DIR__ "dali_huoji":1,
    ]));
    set("owner", "VOID_HEIDIAN");
    set("no_beg", 1);
    set("no_clean_up", 0);

    setup();
}

init()
{
    if (query("owner") == this_player()->query("id"))
    {
        add_action("do_short", "short");
        add_action("do_long", "long");
    }
}
