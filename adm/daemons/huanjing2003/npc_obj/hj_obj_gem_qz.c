//                ��׼��������ʾ��                                   |
// �þ���ңԶ��˵֮��Ե���������� ������Ʒ  �����Ȩ��(������������б�)
// ����Ʒ��� hj_room1.c ���Ѽ�Ȩ��JOB�����ҽ��� hj_npc_kill.c ���졣
// by naihe  2003-10-21  ��ï��
// naihe 05-9-8 7:57 V1.8 �������¡�����һ��Ǳ��������

#include <ansi.h>

inherit ITEM;


string *names = ({
    "��Ұ��Ȩ��",
    "������Ȩ��",
    "������Ȩ��",
    "ɽ����Ȩ��",
    "������Ȩ��",
});

string *ids=({
    "manye quanzhang",
    "mengli quanzhang",
    "aiyao quanzhang",
    "shanguai quanzhang",
    "juren quanzhang",
});

string *longs=({
    "����һ����Ұ���Ȩ�ȣ�ͨ����ڣ�ֻ�а��Ƴ��̣�ȴ����һ���������ǵ����ơ�\n",
    "����һ���������Ȩ�ȣ�ͨ����ڣ�ֻ�а��Ƴ��̣�ȴ����һ���������ǵ����ơ�\n",
    "����һ���������Ȩ�ȣ�ͨ����ڣ�ֻ�а��Ƴ��̣�ȴ����һ���������ǵ����ơ�\n",
    "����һ��ɽ�����Ȩ�ȣ�ͨ����ڣ�ֻ�а��Ƴ��̣�ȴ����һ���������ǵ����ơ�\n",
    "����һ���������Ȩ�ȣ�ͨ����ڣ�ֻ�а��Ƴ��̣�ȴ����һ���������ǵ����ơ�\n",
});

void setme( int iii )
{
    if( iii == 99 || iii < 0 || iii >= sizeof(names) )
        iii = random(sizeof(names));
    set("iii", iii);
    set_name( names[ iii ], ({ ids[ iii ], "quan zhang", "zhang" }) );
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    set("long", longs[ iii ]);
    set("unit", "��");
    set("hj_game/obj","the_gem_qz");
    set("no_refresh", 1); // ����MUDˢ��

    set("value", 1);  // ��������º󲻻���ʧ��
}

void create()
{
    setme(99);
    setup();
}
