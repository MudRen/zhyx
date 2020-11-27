#include <ansi.h> 
inherit ROOM;
string look_gaoshi();

void create ()
{
        set ("short", "���䳡����");
        set ("long", @LONG
���ǡ��л�Ӣ�ۡ����䳡�Ĵ��ţ�һ���߸ߵ�ľ���Ʒ������顺���䳡��
�����ֽ���֡����ﾭ���ٰ�������͵ı����ᡣ���е��˶��л����
�ӡ����Ա���һ�Ÿ�ʾ(gaoshi)��
LONG);
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
        set("no_fight",1);
        set("no_clean_up",1);
        set("exits", ([
                "north"   : __DIR__"zoulang",
                "south"   : "/d/city/ximenroad",
        ]));
        set("objects", ([
                __DIR__"npc/gongping" : 1,
        ]));
        setup();
}

string look_gaoshi()
{
        object ob;

        return "���䳡�����ҿ���ʹ�ã�\n
		"HIY" chaxun ����"NOR" ��ѯ���������Ϣ��\n
		"HIY" canjia ����"NOR" �μӱ�����\n
		"HIY" menpai ����"NOR" �������ɱ�����\n";
}


int valid_leave(object me, string dir)
{
        object ob, where;

        if (!where=find_object(__DIR__"gate"))
                where=load_object(__DIR__"gate");
        ob=present("gongping zi", where);
    
        if ( !wizardp(me) && dir=="north" ) {
        if (!present("men piao", me))
        {
                return notify_fail(CYN"��ƽ��˵�����Բ��𣬸���û����Ʊ��\n"NOR);
        }
                if(me->query("snowzongshi"))
                        return ::valid_leave(me, dir);
                if( ob->query("fangshi")!="������" && !ob->query("start/start"))
                        return notify_fail("����û���κα��䣬�㲻�ܽ�ȥ��\n");
        }
        return ::valid_leave(me, dir);
}

