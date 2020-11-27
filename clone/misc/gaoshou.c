#include <ansi.h>
inherit NPC;

#define GAOSHOU_DIR "/data/leitai/"

void do_biwu();
int is_c_file(string arg);		//�ж�arg�Ƿ�*.c�ļ���ʽ
string do_perform(string perform_skill);
string auto_perform();

object my_enemy;

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = query("id");
	if (! stringp(id)) return 0;
	return sprintf(GAOSHOU_DIR "npc/%s", id);
}

int save()
{
	return 0;
}

int restore()
{
	string file;

	if (stringp(file = this_object()->query_save_file()))
		return restore_object(file);
	return 0;
}

void create()
{
        string id,name;
        mapping my;
        ::create();
        id = BIWU_D->get_id();
        set_name( "�л�Ӣ��" , ({ id }) );
        setup();        

        restore();
        reset_action();
        remove_call_out("do_biwu");
        call_out("do_biwu",0);
}

void do_biwu()
{
        object me,cloth,weapon;
        mapping summon_ob;
        string *carry_ob,*summon_key,weapon_file;
        string the_pfm;
        int i;

        me = this_object();
        my_enemy = BIWU_D->get_enemy();
        if (!my_enemy) return;
        if (environment(my_enemy) != environment())
                return;
        message_vision(HIW"ֻ����һ�����죬$N�Ӻ�̨�����˳���������һ���ķ���\n\n",me);
        if (mapp(summon_ob = me->query("can_summon")) && sizeof(summon_ob))
        {
                summon_key = keys(summon_ob);
                for(i = 0;i < sizeof(summon_key);i++)
                {
                        if (! stringp(weapon_file = summon_ob[summon_key[i]]))
                                continue;
                        call_other(weapon_file, "???");
                        weapon = find_object(weapon_file);
                        if (! weapon || ! weapon->receive_summon(me))
                        {
                               message_vision(HIM "$N" HIM "��������������������"
                                       "�ʡ�\nȻ��ʲôҲû�з��� :)\n", me);
                        }
                }
        }
        if (arrayp(carry_ob = me->query("carry_ob")) && sizeof(carry_ob))
                for(i = 0;i < sizeof(carry_ob);i++)
                {
                        if (objectp(cloth = new(carry_ob[i])))
	                        cloth->move(me);
                }
        command("wear all");
        command("wield all");
        command("yun powerup");
        command("yun shield");
	switch (me->query_skill_mapped("force"))
	{
		case "linji-zhuang":
			command("yun tiandi");
			command("yun daxiao");
			me->set("qi",me->query("max_qi"));
			me->set("jing",me->query("max_jing"));
			break;
		case "huagong-dafa":
			command("yun hua");
			break;
		case "zixia-shengong":
			command("yun ziqi");
			break;
		case "huntian-qigong":
			command("yun haixiao");
			command("yun shengang");
			break;
		case "bibo-shengong":
			command("yun wuzhuan");
			break;
		case "yunv-xinfa":
			command("yun wang");
			break;
		case "nuhai-kuangtao":
			command("yun haixiao");
			break;
		case "xiantian-gong":
			command("yun chunyang");
			break;
		case "longxiang":
			command("yun longxiang");
			command("yun panlong");
			command("yun tunxiang");
			break;
		case "hamagong":
			command("yun reserve");
			break;
		case "lengyue-shengong":
			command("yun freeze");
			break;
		case "kurong-xinfa":
			command("yun kurong");
			break;
	}
		
        message_vision(HIW"\n$N����$n���һ������Ȼ��Ҫ�����Ǿͷ�������ɣ�\n",me,my_enemy);
        the_pfm = auto_perform();
        kill_ob(my_enemy);
        if (the_pfm != "smallfish")
                call_other(the_pfm, "perform", me, my_enemy);
}

int is_c_file(string arg)		//�ж�arg�Ƿ�*.c�ļ���ʽ
{
        int l;
        l = strlen(arg);
        if (arg[l - 1] == 'c' && arg[l - 2] == '.')
                return 1;
        return 0;
}

//      auto_perform()
//      �Զ�������
string do_perform(string perform_skill)
{
        int l;
        string dir;
        string file;
        mixed *all_file;

        if (! stringp(dir = SKILL_D(perform_skill) + "/") || file_size(dir) != -2)	//����书û�о���
        return "smallfish";

        if (file_size(dir + "perform/") == -2)	//����书��һ��perform/��Ŀ¼
                dir += "perform/";

        all_file = BIWU_D->get_the_dir(dir);

        if (!sizeof(all_file))	//����书û�о���
                return "smallfish";

        all_file = filter_array(all_file,(: is_c_file :));	//ȡ��*.c�ļ�
        if (!sizeof(all_file))	//����书û�о���
                return "smallfish";

        file = all_file[random(sizeof(all_file))];	//�����ȡ�书�ľ���
        l = strlen(file);
        file = dir + file[0..l-3];
        return file;
}

string auto_perform()
{
        object me,weapon;
        string askill,the_pfm;
        mapping prepare;
        mapping my_temp;
        int can_auto_perform;	
        string the_perform_skill,perform_skill_1,perform_skill_2;

        me = this_object();
        if (! living(me)) return "smallfish";

        if (! mapp(my_temp = me->query_entire_temp_dbase()))
                my_temp = ([ ]);
        
        prepare = me->query_skill_prepare();
        if (weapon = my_temp["weapon"])
                askill = weapon->query("skill_type");
        else if (! prepare || sizeof(prepare) == 0) askill = "unarmed";
        else if (sizeof(prepare)) askill = (keys(prepare))[0];
        if (askill == "pin") askill = "sword";

        askill = me->query_skill_mapped(askill);

        can_auto_perform = 0;
        if (askill)
        { 
                perform_skill_1 = askill;	//��һ��pfm;
                can_auto_perform = 1;
        }
        //���û��װ���������������п����书bei�ˣ���ôȡ��һ��bei�Ŀ����书�ľ���Ϊ�ڶ���pfm;
        if (!weapon && prepare && sizeof(prepare) > 1) 
                perform_skill_2 = me->query_skill_mapped((keys(prepare))[1]); 

        if (perform_skill_2) can_auto_perform = 2;
        if (can_auto_perform == 1)
                return do_perform(perform_skill_1);
        else if (can_auto_perform == 2)
        {
                //���ѡ������PFM
                if (random(2))
                        the_perform_skill = perform_skill_1;
                else
                        the_perform_skill = perform_skill_2;

                the_pfm = do_perform(the_perform_skill);
                if (the_pfm == "smallfish")
                        the_pfm = do_perform((the_perform_skill == perform_skill_1) ? 
                                                perform_skill_2 : perform_skill_1);
                return the_pfm;
        } else return "smallfish";
}

void unconcious()
{
        die();
}

void die()
{
        message_vision(NOR "\n$Nϥ��һ����ϥ�ŵأ���ǿ����վ������������ȴ���һ��"
                       HIR "��Ѫ" NOR "����Ȼת����ȥ��\n\n" NOR, this_object());

        message("sys",HIW + "����������� ��ϲ" + NOR + HIY + my_enemy->name(1) + NOR + 
                               HIW + "����սʤ" + NOR + HIY + this_object()->name(1) + NOR + 
                               HIW + "��!\n" + NOR,all_interactive());

        BIWU_D->npc_lost();
        destruct(this_object());
}
