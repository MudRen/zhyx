// Updated by yuchang


inherit NPC;
#include <ansi.h>
int big_blowing();
void create()
{
        set_name(HIR"����"NOR, ({ "e long" }) );
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 200);
        set("long", 
"����һ��ȫ���죬�����֮�������������Ķ�����
��ȫ��ɢ���ų��ɫ�Ļ��档\n");
        
        set("str", 100);
        set("con", 100);
        set("dex", 100);

        set("dodge", 999);
        set("force", 999);
        set("unarmed", 999);
        set("parry", 999);
        set("max_qi", 50000);
        set("max_jing", 50000);
        set("max_neili", 50000);
        set("attitude", "aggressive");
        set("limbs", ({ "ͷ��", "����", "β��" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("chat_chance_combat", random(30)+10);
        set("chat_msg_combat", ({
                (: big_blowing :)
        }) );

        set("combat_exp", 51100000+random(600110000));
        set("bellicosity", 30000 );
        
        set_temp("apply/attack", 1560+random(400));
        set_temp("apply/damage",1500+random(400));
        set_temp("apply/armor", 1500+random(400));

        setup();
} 
int big_blowing()
{
        remove_call_out("hurting");
        message_vision( HIR "\n\n�������������һ������ȫ��תΪ�ʺ�Ļ�ɫ�����������ʹ��˼�������\n\n" NOR,
                        this_object());
        call_out("hurting", random(1)+1);


        return 1;
}

int hurting()
{
        int i;
        int dam;
        object *inv;
        message_vision( HIR "\n\n�����³�һ�ɳ�ɷٽ�Ļ��森����������ƺ�����ȼ���ţ�����\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
                dam = random(1000)+100;
                if(dam <0) dam = 0;
                inv[i]->receive_wound("qi",dam);
                COMBAT_D->report_status(inv[i],1);
        }
        return 1;
}
void init() 
{ 
        object me, ob; 

        ::init(); 
        if (! interactive(me = this_player())) 
               return; 

       // �Զ�������� 
       if ((int)me->query_skill("force", 1) > 100 
          && ! this_object()->query("no_auto_kill") && me->query("age") > 13)
       { 
               remove_call_out("kill_ob"); 
               call_out("kill_ob", 0, me); 
        } 
            remove_call_out("disappear"); 
             call_out("disappear", 20); 
     } 
void die()
{
        object obj;
        object killer;
        int exp,userexp;
        
         if(objectp(killer=this_object()->query_last_damage_from()))
        {
                userexp=killer->query("combat_exp");
                exp=((int)killer->query("literate")*2)+random(1000)+10000+(userexp);
                obj = new("/d/zhuanshi/obj/quan");
                obj->move(killer, 1);

                if (!killer->query_temp("m_success/����"))
                {
                        killer->set_temp("m_success/����",1);
                        killer->add("combat_exp",exp);
                        killer->add("potential",20000);
                        message("channel:chat", HBMAG"��ת����"+killer->query("name")+"�ɹ���ɱ���˶���!�õ�������Ȧ!\n"NOR,users());
                }
                
                tell_object(killer, HIR "\n\nһ�Ż����͵����ڣ�һ������˵����лл��ɱ���������㽫�õ����Ȧ��Ϊ����������\n" NOR); 
                message_vision("һ���������������ҫ��$N��\n", killer);
                tell_object(killer, HIM "\n��Ȼ�㷢�����Ѿ�������һ��İ���ķ���\n" NOR);
                killer->move("/d/city/wumiao");
                message_vision("�����ȥ����ͻȻ���ֺ�������һ���ˡ�\n", this_object());
        }
        message_vision("$N����һ������ȥ��\n", this_object());
        destruct(this_object());
} 
