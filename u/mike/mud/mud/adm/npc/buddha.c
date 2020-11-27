//����(ת��npc)

#include <ansi.h>
inherit  NPC;
inherit  F_SAVE;

int ask_reborn(); 

static string *word = ({
"��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "Ӧ", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "˼", "��", "��", "ʧ",
});

void create()
{
        seteuid(getuid());
        restore();
        set_name(HIY "����Ĳ��" NOR, ({ "buddha", "fo zu", 
                "fo", "shijia muni" }));
        set("long", @LONG
����ׯ�ϱ������˲������ӡ�
LONG);

        if (clonep())
                destruct(this_object());
        else {
                set("nickname", HIW "���編��" NOR);
                set("title", HIC "����" NOR);
                set("gender", "����" );
                set("age", 500);
                set("attitude", "friendly");
                set("max_jing", 99999);
                set("max_qi", 99999);
                set("max_jingli", 99999);
                set("jingli", 99999);
                set("max_neili", 99999);
                set("neili", 99999);
                set("jiali", 9999);
                set("str", 99);
                set("int", 99);
                set("con", 99);
                set("dex", 99);
                set("combat_exp", 99999999);

                set_skill("dodge", 999);
                set_skill("unarmed", 999);
                set_skill("force", 999);
                set_skill("parry", 999);
                set_skill("sword", 999);      
                set_skill("medical", 999);       
                set_skill("literate", 999);
                set_skill("lamaism", 999);
                set_skill("buddhism", 999);  
                set_skill("shaolin-yishu", 999); 
                set_skill("idle-force", 999);
                set_skill("huntian-baojian", 999);
                set_skill("lunhui-jian", 999);
      
                map_skill("force", "huntian-baojian");       
                map_skill("parry", "lunhui-jian");    
                map_skill("sword", "lunhui-jian");     
                map_skill("medical", "shaolin-yishu");   

                set("inquiry", ([ 
                    "ת������" : (: ask_reborn :), 
                ])); 
                set("chat_chance_combat", 200);
                set("chat_msg_combat", ({
                        (: perform_action, "sword.hui" :),
                        (: exert_function, "recover" :),
                        (: exert_function, "powerup" :),
                        (: exert_function, "shield" :),
                        (: exert_function, "heal" :),
                        (: exert_function, "dispel" :),
                        (: exert_function, "regenerate" :),
                }));
             }

        setup();        
        carry_object("d/city/obj/jiasha")->wear();
        carry_object("/d/city/obj/changjian")->wield(); 
}

// ����ʱ�������
void remove()
{
        save();
}

// �����ĵ�
string query_save_file()
{
        return "/data/reborn/buddha";
}

void init()
{
     add_action("do_decide", "decide");

}


int ask_reborn()
{
    object me;
    me = this_player();

    command("look " + me->query("id"));

    if ( me->query("reborned") )
    {
       command("say ��İ���Үʶ�����Ѿ�������");
       return 1;
    }


 /*   if ( ! me->query("reborn_ok") ) //�ж��Ƿ����������ת������
    {
        command("say �����û���������ľ���ɣ�");
        return 1;
    }*/
    
    command("say �����Ҳ�Դ����е�������Ҫ̽Ѱ����������");
    command("say ��Ҫת������֮��ѧ�ͽ����٣����Ը�⣿");
    message_vision(HIC"$N" HIC"��$n" HIC"�������������Ѿ�������"
                   "decide�ɣ�\n"NOR, this_object(), me);
    me->set_temp("reborn_start/ask",1);
    return 1;
}

int do_decide()
{
    int i;
    string msg;


    object me = this_player();
    msg = "";
    

    if ( ! me->query_temp("reborn_start/ask"))
        return 0;

    tell_object(me, HIW"�����������˵�����Ҹ�����һ����"
                "��ɲ���һ����ɶ��˼��\n����������Ե�ټ����ң�"
                "ƾ�˽����һ���㿪��ǰ�����䣡\n"
                "�˽����뵱�������ģ��м��мǣ�\n"NOR);

    for( i = 0; i < 5; i++)
        msg += word[random(sizeof(word))];

    tell_object(me, HIY"\n�����������˵��������Ľ����ǣ�"HIR + msg + "\n"NOR);
    tell_object(me, HIY"��������?�Ҽ��̾�����ȥͶ̥��!\n\n"NOR);

    remove_call_out("reborn");
    call_out("reborn", 5, me, msg);
    return 1;
}

int reborn(object me, string msg)
{
    int i;

    set("data/" + me->query("id") + "/reborn_time", time());
    set("data/" + me->query("id") + "/pass", msg);

    set("data/" + me->query("id") + "/str", me->query("str"));
    set("data/" + me->query("id") + "/int", me->query("int"));
    set("data/" + me->query("id") + "/con", me->query("con"));
    set("data/" + me->query("id") + "/dex", me->query("dex"));
   
    set("data/" + me->query("id") + "/sun", me->query("gift/sun"));
    set("data/" + me->query("id") + "/water", me->query("gift/water"));
    set("data/" + me->query("id") + "/feng", me->query("gift/feng"));
    set("data/" + me->query("id") + "/light", me->query("gift/light"));

    for( i = 0; i < sizeof(me->query("special_skill")); i++)
      
       set("data/" + me->query("id") + "/special_skill/" + i, 
            keys( me->query("special_skill"))[i] );
    

    save();       

    message("vision", HIG"����紫�š�" + me->query("name") + "(" + 
             me->query("id") + ")" + "�ѵ÷����׼����ʱת��������\n"NOR, users());

    message_vision("ֻ��$N����һ�����̣�������ʧ�ˡ���\n", me);

    UPDATE_D->remove_user(me->query("id"));

    return 1;
}


