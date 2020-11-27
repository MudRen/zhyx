// Updated by yuchang
inherit NPC;
#include <ansi.h>
void big_blowing();

void create()
{
        set_name(HIR"������"NOR, ({ "huo qilin", "qilin" }) );
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 200);
        set("long", 
"����һ��ȫ���죬�����֮��Ļ���������Ļ����룡
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

        set("chat_chance_combat", 80); 
        set("chat_msg_combat",({(: big_blowing :)}));      
        set("combat_exp", 51100000);
        set("bellicosity", 30000 );
        
        set_temp("apply/attack", 1560+random(400));
        set_temp("apply/damage",1500+random(400));
        set_temp("apply/armor", 1500+random(400));

        setup();
} 

void big_blowing()
{
     int i, dam;
     object *inv, me, ob;

     ob = this_object();        
     me = this_player();

     tell_room(environment(ob),HIR "\n\n������ͻȻ�³�һ�ɳ�ɷٽ�Ļ��棬"
                  "��������ƺ����������ˣ�����\n\n"NOR);


     inv = all_inventory(environment(ob));
     for(i = 0; i < sizeof(inv); i++)
     if( living(inv[i]) && inv[i] != ob )
     {
                dam = random(500) + 100;               
                inv[i]->receive_wound("qi",dam);
                tell_object(inv[i], HBRED"�㱻�������ţ��پ���Ѫ�������ˣ�\n\n"NOR);
     } 
}



void init() 
{ 
        object me, ob; 

        ::init(); 
        if (! interactive(me = this_player())) 
               return; 

       // �Զ��������                
       kill_ob(me); 
} 
void die()
{
        object ob, obj;
        object killer;
        int exp, userexp;

        ob = this_object();
        message_vision(HIR"\n$N" HIG"�����˼��£�����һ���ҽУ��㲻�ٶ����ˡ�\n"NOR, ob);

        if(objectp(killer = ob->query_last_damage_from()) &&
           ! killer->query("reborn_start/qilindong/qilin") )
        {
                userexp = killer->query("combat_exp");
                exp=((int)killer->query("literate")*2)+random(1000)+10000+(userexp);
                obj = new(__DIR__"obj/qilin");
                obj ->move(killer, 1);
               
                message_vision(HIC "\n\nһ�Ż����͵����ڣ�һ��������$N˵����"
                               "лл��ɱ�������룬�㽫�õ��������Ϊ������\n\n" NOR, killer); 
                message_vision(HIY"ֻ��$N" HIY"������ʧ��ֻʣ����һֻ�����ǰ�ۡ�\n"
                               "\n$n�漴������ۼ���������\n\n"NOR, ob, killer);            
                killer->set("reborn_start/qilindong/qilin",1);
                killer->add("combat_exp",exp);
                killer->add("potential",20000);                       
                message("vison", HBMAG"��ת�����š�����˵" + killer->query("name") +
                                "�ɹ���ɱ���˻����룬�õ����������!\n"NOR, users());
        }              
        destruct(ob);
} 
