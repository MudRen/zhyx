inherit NPC;
#include <ansi.h> 
int ask_me();
int cure_lighting(); 
int kill_lighting(); 
void create()
{
        set_name(HIY"ҹ"+HIG"��"NOR, ({ "night" }) );
        set("gender", "Ů��"); 
        set("title", HIC"����֮��"NOR);
        set("age", 20);
        set("long",@LONG
�����Ǿ����֮�����������о���ĵ��������ı�����һ��͸������
��ɢ���ž����Ĺ�â�����������У�����һ�ѱ�����͸���ĳ�����
�Ǿ��Ǿ����ı�������鵶����΢΢Ư���ڿ��У���Ȼ��û�б�
�˵����ƣ���ȴ����һ�����ϵ����ϡ�
LONG);        
        set("str", 18);
        set("con", 52);
        set("dex", 100); 
        set("per", 100);
        set("max_qi", 50100);
        set("max_jing", 50100); 
        set("neili", 50010);
        set("max_neili", 50010);
        set("attitude", "peaceful"); 
        set_skill("dodge", 1400); 
        set_skill("blade", 1300); 
        set_skill("parry", 1300); 
        set_skill("force", 1300);  
        set_skill("music", 1300);
        set_skill("spirit-dodge", 1300); 
        set_skill("spirit-blade", 1300); 
        map_skill("dodge", "spirit-dodge");
        map_skill("blade", "spirit-blade");
        map_skill("parry", "spirit-blade"); 
        set("chat_chance_combat", random(20)+30); 
      set("inquiry", ([
            "�ָ�" : (: ask_me :),
        ]) );
        set("chat_msg_combat", ({
               (: cure_lighting :), 
         }) );

                set("combat_exp", 20010000+random(20110000));
        
        set_temp("apply/attack", 360+random(500));
        set_temp("apply/damage",500+random(500));
        set_temp("apply/armor", 500+random(500));

        setup(); 
        carry_object("/quest/tulong/obj/book");
 } 
void init()
{ 
       add_action("do_kill","hit");
       add_action("do_kill","kill");
} 

int do_kill(string arg)
{   
    object me, ob; 
    string callname;
    ob=this_player();
    me=this_object();

        callname = RANK_D->query_rude(me);
        if (random(3) > 1)
        message_vision("\n$N����$n�ȵ�����" 
                + callname + "�����ղ������������һ��\n\n", ob, me);
        else
        message_vision("\n$N����$n�ȵ�����" 
                + callname + "��������վ�����ļ��գ���\n\n", ob, me); 

       call_out("kill_player",1); 

        return 1;
}

int ask_me()
{ 
       object me = this_player();

       if(me->query_temp("m_success/���")) {       remove_call_out("cure_lighting");
 
       command("smile"); 
       command("say �����ȹ��ҵ�������Ӧ�ø��㲹����");
       call_out("cure_lighting",3); 

       return 1;
       } 
       command("? " + me->query("id"));
       return 1;
}
 
int kill_player()
{
    object me, ob;
    ob=this_player();
    me=this_object();

        me->command("sigh");
        me->command("say �����ֺοࣿ"); 
        me->command("getblade");
        me->command("wield blade");
        me->set("chat_msg_combat", ({ 
               (: kill_lighting :), 
         }) );
         remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
        return 1;
}
int cure_lighting()
{
remove_call_out("curing");
message_vision( HIY "\n\nҹ"+HIG"��"+HIC"����չ������������ɵ���գ�����ɢ������͵Ĺ�â����\n\n" NOR,
this_object());
call_out("curing",random(1)+1);

        return 1;
} 

int curing()
{ 
        int fw;
        object me = this_object();
        int i;
        int dam;
        object *inv;
        message_vision( HIY "\n\nҹ"+HIG"��"+HIC"˫�ֻ�����ǰ����â�������£�����\n\n",this_object()); 
                fw = (int)me->max_food_capacity();
                me->set("food", fw);
                fw = (int)me->max_water_capacity();
                me->set("water", fw);
                me->set("jing",me->query("max_jing"));
                me->set("eff_jing",me->query("max_jing"));
                me->set("qi",me->query("max_qi"));
                me->set("eff_qi",me->query("max_qi"));
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
        dam = random(200)+200;
        if(dam <0) dam = 0;
        inv[i]->receive_curing("qi",dam); 
        inv[i]->receive_heal("qi",dam);
  tell_object(inv[i], HIG "����ԡ�ڹ�â������Լ����ָ��ˣ�\n"NOR);
         }
        return 1;
}  
int kill_lighting()
{
remove_call_out("hurting");
message_vision( HIY "\n\nҹ"+HIG"��"+HIC"����չ������������ɵ���գ�˫��ҫ��һ�Ź�â����\n\n" NOR,
this_object());
call_out("hurting",random(1)+1);


        return 1;
}

int hurting()
{
        int i;
        int dam;
        object *inv;
        message_vision( HIY "\n\nҹ"+HIG"��"+HIC"˫�ֽ�ӡ����ʱ���â��ʢ����ؼ�ֻʣһƬҫĿ�Ĺ�â������\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
        dam = random(200)+100;
        if(dam <0) dam = 0;
        inv[i]->receive_wound("qi",dam);
        COMBAT_D->report_status(inv[i],1);
        }
        return 1;
}

