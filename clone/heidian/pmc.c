#include <room.h>
#include <ansi.h>
#include <getconfig.h>

inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"��ɫ����"NOR);
    set("long", @LONG
������һ�����Ĵ󷿼䣬��һ���������۲��õĽ��ҫ����
���˫�ۡ������⻪�����׵�װ�Σ����ŵô��������ҳ���������
ǰ����һ�ž����Ĵ����ӣ�һ�ѽ�ɫ��Ӿ����İڷ��������ϣ���
������վ�����Ӻ��棬Ϭ�����۹��ƺ�Ҫ�����͸���㲻�ɸо���
����Ѫ�ڷ��ڡ�������ǽ�ϣ�����һ������(paizi)������д����
������Ͳ����ֲᡣ������ǽ�ϣ�������һ������(board)������
д����ʦ�����ֲᡣ
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);

    set("objects", ([
        "/adm/npc/fjtx" : 1,
    ]));

    set("exits", ([
        "south"  : "/d/city/pm_restroom",
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

    if (arg != "paizi" && arg != "board") return 0;

    if (!wizardp(this_player()) && arg == "board")
    {
        write("�㲻����ʦ��������������д���֡�\n");
        return 1;
    }

    if (arg == "paizi")
    {
        msg = HIC + LOCAL_MUD_NAME() + HIY "�ڵ�����" HIC " ����\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
        msg += HIW "��һ������������ʼʱ�ر�һ�й���Ƶ����\n" NOR;
        msg += HIW "�ڶ�������ʹ���κι���Ƶ��˵�κλ���\n"NOR;
        msg += HIW "�������������ʹ��emote��\n"NOR;
        msg += HIW "���ģ�������㿪�ڽ�̸�����轻̸����ʹ��"HIY"team talk"HIW"��\n"NOR;
        msg += HIW "���壺����ʹ���κη�ʽɧ�����������ߣ�\n"NOR;
        msg += HIW "������������Ǯ����ʤ��������ߵ���һ��úڵ꾭ӪȨ��\n"NOR;
        msg += HIW "���ߣ�ÿ��������һ��ֻ�ܻ��һ���ڵ�ľ�ӪȨ��\n"NOR;
        msg += HIW "�ڰˣ��κ�Υ�������涨����ң�����ȡ�������ʸ�\n"NOR;
        msg += HIW "�ھţ�����ָ�"HIY"jupai <�Ӽۻƽ���Ŀ>"HIW"��ȱʡΪ�Ӽ�100���ƽ�\n"NOR;
        msg += HIW "��ʮ����ʦ����ȫ������Ȩ����\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
    } else
    {
        msg = HIC + LOCAL_MUD_NAME() + HIY "�ڵ�����" HIC " ��ʦ�����ֲ᣺\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
        msg += HIW "��һ������������������ǰȷ���Ѿ���ʼ�����кڵ꣨"HIY"cshshop"HIW"����\n" NOR;
        msg += HIW "�ڶ���������������ָ�"HIY"start [�������]"HIW"����ʹ�ò�����ʾ�ֹ�������\n"NOR;
        msg += HIW "������*����ĳ���ڵ�ʹ��ָ�"HIY"paimai <�ڵ�ID>"HIW"��\n"NOR;
        msg += HIW "���ģ�*���ֹ�����תΪ�Զ�����ָ�"HIY"autopaimai"HIW"��\n"NOR;
        msg += HIW "���壺�鿴�������ָ�"HIY"paimailist"HIW"��\n"NOR;
        msg += HIW "������ȡ��|���� ��������ʸ�ָ�"HIY"unwelcome <id> [1|0]"HIW"��ȱʡΪ1��\n"NOR;
        msg += HIW "���ߣ�*���������۸��Լ����ָ�"HIY"qiao"HIW"��\n"NOR;
        msg += HIW "�ڰˣ�*��������ָ�"HIY"finish"HIW"��������ȫ���ڵ�ȫ��������ϲ���ʹ�ã���\n"NOR;
        msg += HIW "�ھţ����д�"HIY"*"HIW"��ָ���ʾֻ��������������ʦ���ܹ�ʹ�ã�\n"NOR;
        msg += HIW "��ʮ��������ʦ���ߡ��뿪�����ߡ�������������ת��Ϊ�Զ����̡�\n"NOR;
        msg += HIC "-------------------------------------------------------------\n" NOR;
    }
    write(msg);
    return 1;
}
