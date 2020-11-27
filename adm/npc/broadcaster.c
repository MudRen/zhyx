#include <ansi.h> 
inherit NPC; 

void receive_message(string msgclass, string msg);
      
void create() 
{ 
        set_name(HIY "��ӹ" NOR, ({ "jin yong", "jin", "yong" }) );
        set("title", HIG"����ʼ��" NOR);
        set("nickname", HIC"һ֧��ʾ��滳"NOR);
        set("gender", "����");
        set("age", 35);
        set("no_get", 1);
        set("long",
           "�������������Ĵ�ʼ�˽�ӹ�������\n");
        set("env/immortal",1);
        set("env/invisible",1);
        set_heart_beat(1);
        setup(); 
}
       
void heart_beat()
{
        int status;
        object enemy,npc;
        status = BIWU_D->get_status();
        if (status != 2) return;

        enemy = BIWU_D->get_enemy();
        npc = BIWU_D->get_npc();
        if (!objectp(enemy) || 
            !living(enemy) || 
            base_name(environment(enemy)) != "/d/leitai/leitai" ||
            !interactive(enemy))
        {
                if (objectp(enemy) && base_name(environment(enemy)) == "/d/city/biwu_dating")
                {
                        message_vision(HIC"�����󺺳�����̨����æ���ҵİ�$Ņ���ˡ�\n"NOR,enemy);
                        enemy->move("/d/city/biwu_restroom");
                        message_vision(HIC"��������æ���ҵİ�$Ņ�˽�����\n"NOR,enemy);
                }        
                if (objectp(npc)) 
                {
                        message_vision(HIW"$N���һ������һ���·��ϵĳ�����ת���߽���̨����\n"NOR,npc);
                        destruct(npc);
                }
                BIWU_D->finish_biwu();
        }
        return;
}
