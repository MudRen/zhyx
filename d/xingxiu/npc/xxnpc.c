// Code of ShenZhou
#include <ansi.h>
#include <room.h>

inherit NPC;
string do_move();

void create()
{
        switch( random(10) )
        {
        case 0:
        set_name("�߿���", ({ "gao kexin", "gao", "kexin" }) );

        set("long","���ǻ�ɽ�ɸ��֣��Ӷ������������ɥ����а����ʿ����������\n");
        set("gender", "����");
        set("age", 20+random(32));
        set("menpai", "huashan");
                break;

        case 1:
        set_name("����", ({ "jue xing", "jue", "xing" }) );

        set("long","�ƺ���������֧���书��ǿ��������淢��Ҫɨ������аħ��\n");
        set("gender", "����");
        set("age", 60 + random(4));
        set("int", 30);
        set("menpai", "shaolin");
        break;

        case 2:
        set_name("��־��", ({ "liu zhixiu","liu" }) );
        set("gender", "����");
        set("age", 30+random(20));
        set("long","����һ��˫Ŀ������׳���ʿ������ȫ�档\n");
        set("menpai", "quanzhen");
        break;
        
        case 3:
        set_name("����", ({ "jing ci", "jing", "ci" }) );
        set("long","һ������޳�������������С��ã���˵���ո�ǿ��\n");
        set("gender", "Ů��");
        set("age", 20 + random(4));
        set("int", 30);
        set("con", 30);
        set("menpai", "emei");
        break;
 
        case 4:
        set_name("����", ({ "jing ci", "jing", "ci" }) );
        set("long","һ������޳�������������С��ã���˵���ո�ǿ��\n");
        set("gender", "Ů��");
        set("age", 20 + random(4));
        set("int", 30);
        set("con", 30);
        set("menpai", "emei");
        break;

        case 5:
        set_name("����", ({ "jue yu", "jue"}) );

        set("long","�ƺ���������֧���书��ǿ��������淢��Ҫɨ������аħ��\n");
        set("gender", "����");
        set("age", 60 + random(4));
        set("int", 30);
        set("menpai", "shaolin");
        apply_condition("drunk",20);
                break;
        case 7:
        set_name("����", ({ "jue ci", "jue", "ci" }) );
        set("long","�ƺ���������֧���书��ǿ��������淢��Ҫɨ������аħ��\n");
        set("gender", "����");
        set("age", 60 + random(4));
        set("int", 30);
        set("menpai", "shaolin");
        apply_condition("drunk",20);
        break;
        
        case  8:
        set_name("�����ֿ�", ({ "guaike", "ke", "baishan guaike" }) );
        set("long","һ�����Ű����Ĺֿ͡�\n");
        set("gender", "����");
        set("age", 30 + random(4));
        set("int", 30);
        set("con", 30);
        set("menpai","mingjiao");
        break;
        
        case  9:
        set_name("Ҷ��ɽ", ({ "ye sanshan", "ye", "sanshan" }) );
        set("long","�䵱�����ͣ�������һ�˵غ�ɨ��ɽ���Դ�Ϊ����\n");
        set("gender", "����");
        set("age", 30 + random(4));
        set("int", 30);
        set("con", 30);
        set("menpai", "wudang");
        break;
        
        case  10:        
        set_name("Ҷ��ɽ", ({ "ye sanshan", "ye", "sanshan" }) );
        set("long","�䵱�����ͣ�������һ�˵غ�ɨ��ɽ���Դ�Ϊ����\n");
        set("gender", "����");
        set("age", 30 + random(4));
        set("int", 30);
        set("con", 30);
        set("menpai", "wudang");
        break;
        
        default:
        set_name("�����ֿ�", ({ "guaike", "ke", "baishan guaike" }) );
        set("long","һ�����Ű����Ĺֿ͡�\n");
        set("gender", "����");
        set("age", 30 + random(4));
        set("int", 30);
        set("con", 30);
        set("menpai", "mingjiao");
        break;
        }

        set("attitude", "peaceful");
        set("combat_exp", 20000);
        set("xxtarget",1);

        
        set("inquiry", ([ 
                "ս��"   : (: do_move :),
                "challenge"  : (: do_move :),
        ]) );

        set("auto_perform",5);
        setup();
        carry_object("/clone/cloth/tiejia")->wear();
}



int accept_fight()
{
        object npc = this_object();
        object me  = this_player();
        
        mapping myfam;

        myfam= me->query("family"); 

        if (myfam["family_name"] == "������"){
                command("say ���ñ����ˣ����������ɣ�");
                if( !npc->is_killing(me) ) npc->kill_ob(me);    
        }
        else {
                command("shake");
                command("say ��Ҷ��ǽ���ͬ�����޹ʶ����������˺�����");
                return 0;
        }
        return 1;
        
}

void die()
{
        object ob, corpse, killer;

        if( !living(this_object()) ) revive(1);
 
        if( objectp(killer = query_temp("last_damage_from")) ) 
        {
        	if( !(killer->query("xbiao/dest")) )
        	{
                if(killer->query("id")==this_object()->query("player")){
                	ob = new("/d/xingxiu/obj/lingpai");
                	ob->move(environment());
                	message_vision("ֻ����ž��һ������"+query("name")+"���ϵ�����һ�����¡�\n", this_player());
                	ob->set("player", killer->query("id"));
                	ob->set("menpai", query("menpai"));
                }
            }
        }
    
        if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
                corpse->move(environment());
        remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());
        dismiss_team();
        destruct(this_object());
}

void destroying(object me)
{
        message_vision("$N���˿����⣬�������µ��뿪�ˡ�\n",me);
        destruct(me);
        return;
}

string do_move()
{
    object player, room;
    mapping exits;
    string  *dirs;

    player = this_player();
    if (query("player_name") == player->query("id")) {
        room = environment(this_object());
        exits = room->query("exits");
        dirs = keys(exits);
        command("go "+dirs[random(sizeof(dirs))]);
        return "��ȥ�ͳ�ȥ����ʲô���ң�";
    }else {
        return "�ҽ��첻��������ģ�����һ��ȥ��";
    }
}

