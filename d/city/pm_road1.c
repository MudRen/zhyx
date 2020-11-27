#include <room.h>
#include <ansi.h>
#include <getconfig.h>

inherit ROOM;

#define HEIDIAN "beijing"
#define HEIDIAN_NAME "�����ڵ�"

int do_look(string arg);

void create()
{
    set("short", HIY"��ɫ����"NOR);
    set("long", @LONG
������һ����̻Ի͵����ȣ�ǰ��ͨ��������Ϣ�ң�ǽ����
����һ��ڵ׽��ֵĴ���(dabian)���������Ⱦ������࣬���˲�
�Ҵ���������
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("exits", ([
        "south"  : __DIR__"pmc",
        "north"  : __DIR__"pm_road2",
    ]));

    set("no_clean_up", 0);
    setup();
}

void init()
{
    add_action("do_look","look");
}

int do_look(string arg)
{
    int i;
    object pms;
    string msg;
    mapping *heidian_record;

    if (arg != "dabian") return 0;
    pms = load_object("/adm/npc/fjtx");
    heidian_record = pms->query(HEIDIAN);
    destruct(pms);
    msg = HIC +LOCAL_MUD_NAME()+ HIY HEIDIAN_NAME HIC " ����������\n"NOR;
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    if (!sizeof(heidian_record))
        msg += HIY "Ŀǰ��û�����ݡ�\n";
    else
    {
        msg += sprintf(HIW"%s\t\t\t%-30s%-10s%s\n"NOR,"����","����ʱ��","����ʦ","�۸�");
        for (i = 0;i < sizeof(heidian_record);i++)
            msg += sprintf(HIY"%s(%s)\t\t%-30s%-10s%d\n"NOR,
                   heidian_record[i]["name"],
                   heidian_record[i]["id"],
                   ctime(heidian_record[i]["time"]),
                   heidian_record[i]["pms"],
                   heidian_record[i]["value"]
                   );
    }
    msg += HIC "-------------------------------------------------------------------------\n" NOR;
    write(msg);
    return 1;
}
