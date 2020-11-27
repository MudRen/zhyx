// Code of ShenZhou
// coding by Slow
#include <ansi.h>
inherit NPC;

int auto_perform();
void you_out();
void create()
{
        set_name("����", ({"xiao feng", "xiao", "feng"}));
        set("nickname", "����");
        set("gender", "����");
        set("age", 35);
        set("long", 
"������ǿ�ΰ����ʮ������ͣ�����ɫ�ɲ��ۣ���΢�����ã�Ũü���ۣ�
�߱����ڣ�һ���ķ��Ĺ����������з�˪֮ɫ������֮�ʣ��������ơ�\n");
        set("attitude", "peaceful");
        
        set("str", 30);
        set("int", 24);
        set("con", 40);
        set("dex", 40);

        set("max_qi", 10000);
        set("max_jing", 3000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jingli", 10000);
        set("max_jingli", 9000);
        set("eff_jingli", 9000);
        set("jiali", 100);
        
        set("combat_exp", 5400000);
        set("auto_perform",1);

        set("score", 200000);
        set("death_times",200);

        set_skill("force", 200);             // �����ڹ�
        set_skill("huntian-qigong", 200);    // ��������
        set_skill("strike", 200);            // �����Ʒ�
        set_skill("dragon-strike", 200);   // ����ʮ����
        set_skill("dodge", 200);             // ��������
        set_skill("xiaoyaoyou", 200);        // ��ң��
        set_skill("parry", 200);             // �����м�
        
        map_skill("force", "huntian-qigong");
        map_skill("strike","dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        prepare_skill("strike", "dragon-strike");
        create_family("ؤ��", 13, "����"); 
        setup();
        
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_kill(object victim)
{
        object *ob;
        int i;
        object me=this_object();
        if (!living(me)) return 1;
        if(victim->query_temp("azi/killer")!=1 && victim->query_temp("azi/killer2")!=1)
        {
                command("say �����а��֣�������ĳ��ʱ�¹��˶࣡\n");
                message_vision(HIY "��������˰��֣���������,�ѽ���ʮ���Ʒ��ӵ�����,ֻ������˫�ۻ�Ȧ�Ƴ�������һ�С������лڡ�!\n" NOR,me);
                command("halt");
                ob = all_inventory(environment(me));
                for(i=0; i<sizeof(ob); i++) {
                        if(living(ob[i])  && ob[i]->query_temp("azi/killer2")==1) {
                                tell_object(ob[i], "��е�һ��ǿ�ҵ�����ӿ���ؿڣ��ؿ�һ�ơ�\n");
                                            ob[i]->unconcious();
                        }
                }
                tell_object(victim, "��е�һ��ǿ�ҵ�����ӿ���ؿڣ��ؿڵ�ʱһ�ơ�\n");
                if (victim) victim->unconcious();
                call_out("destruct_me",1,me);
                me->start_busy(5);
        }
        return 1;
}

void die()
{
        object  me =this_object();
        object  ob;
        ob = me->query_last_damage_from();
        if (ob) ob->set_temp("xiaofeng/done",1);
        message_vision(HIR"�����:����,�������,�����������ˣ�\n" NOR,this_object());
        you_out();
        ::die();
}

void destruct_me(object me)
{
        object obj;
        obj=find_object("a zi");
        if (!obj) obj = present("a zi", me);
        if (!obj) obj = present("a zi", environment(me));
        if (obj)
        {
               destruct(obj);
               message_vision(HIY"���������Ц����:�����Ķ��Ȳ�������ס���ϣ��������䣬���Ѳ�����\n" NOR,this_object());
               destruct(me);
        }
}

void you_out()
{
        object ob1,ob2,player;
        object me=this_object();
        ob1=present("you tanzhi");
        if (!ob1)
        {
                seteuid(getuid());
                ob1=new("/kungfu/class/xingxiu/you.c");
                ob1->move(environment());
        }
}

