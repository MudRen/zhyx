// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("�л�Ӣ��", ({ "ying xiong", "ying", "xiong", "hero" }));
        set("long", @LONG
�����Ǵ�˵�е��л�Ӣ�ۣ������������������
�������Ϣ��
LONG);
        set("nickname", HIW "������˫" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
        set("age", 68);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([
                "����"  :"Ҫ�������������ӣ������������������Ȼ�� team bunch <�����> �Ϳ����ˡ�\n",
                "���"  :"Ҫ�������������ӣ������������������Ȼ�� team bunch <�����> �Ϳ����ˡ�\n",
                "����"  :"Ҫ�������������ӣ������������������Ȼ�� team bunch <�����> �Ϳ����ˡ�\n",
        ]) );

        setup();
        carry_object("d/city/obj/cloth")->wear();
/*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(CYN "\n$N" CYN "Ц����������λ����Ҫ������\n"
                               NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
*/
}
