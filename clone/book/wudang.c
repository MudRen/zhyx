// wudang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "�����ر�" NOR, ({ "liandan miben", "miben" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����Ƶ��鼮��������С׭��"
                            "д�š������ر��������֡�\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "liandan-shu",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 155,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "shujing"  : 80,        // �����絤
                        "dieda"    : 80,        // ����������
                        "jiedu"    : 100,       // ţ�ƽⶾ��
                        "yuzhen"   : 150,       // ����ɢ
                        "yuling"   : 150,       // ����ɢ
                        "yuqing"   : 200,       // ����ɢ
                        "sanhuang" : 250,       // ���Ʊ�����
                ]));
        }
        setup();
}
