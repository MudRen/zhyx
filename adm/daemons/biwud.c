//biwud.c
//edit by yuchang

#include <ansi.h>
#include <localtime.h>
#include <command.h>

inherit F_DBASE;

#define BIWU_ROOM "/d/leitai/leitai"
#define newhigh_room "/u/yuchang/workroom"
#define GAOSHOU_OBJ "/clone/misc/gaoshou"
#define TEMP_OBJ "/clone/misc/temp_gaoshou"
#define GAOSHOU_DIR "/data/leitai/"

object the_enemy = 0;
object the_npc = 0;
int open_biwu = 1;
int can_biwu = 1;
int paiming = 10;
string the_id = "";
mapping all_npc = ([]);
mapping tmp_map = ([]);
string *armor_type = 
({
        "armor",
        "boots",
        "cloth",
        "hands",
        "head",
        "neck",
        "shield",
        "surcoat",
        "waist",
        "wrists"
});

int get_status();
object get_enemy();
object get_npc();
string get_id();
string get_new_id();
mapping get_list();
void start_biwu(object me);
void do_biwu(int num);
int csh_paiming();
void save_paiming();
void npc_lost();
void finish_biwu();
mixed *get_the_dir(string dir);

int clean_up() { return 1; }

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "���侫��");
        CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������");
        csh_paiming();
}

//����ֵ 1 -- ������ȥ
//����ֵ 2 -- ���ڱ���
//����ֵ 3 -- ��û����

int get_status()
{
        if (!open_biwu) return 3;
        if (!can_biwu)  return 2;
        return 1;
}
object get_enemy()
{
        return the_enemy;
}

object get_npc()
{
        return the_npc;
}

string get_id()
{
        return the_id;
}

string get_new_id()
{
        if (the_enemy)
                return the_enemy->query("id");
        else
                return "VOID";
}

mapping get_list()
{
       return all_npc;
}

void start_biwu(object me)
{
        if (!csh_paiming())
        {
                tell_object(me,"�Բ�����̨��¼�д�������ϵ��ʦ��\n");
                return;
        }
        the_enemy = me;
        tmp_map["id"] = me->query("id");
        tmp_map["title"] = me->short();
        me->set("last_biwu_time",time());
        can_biwu = 0;
        paiming = 5;
        do_biwu(paiming);
        return;
}

void do_biwu(int num)
{
        int i;
        object ob;
        if (num < 0)
        {
                finish_biwu();
                return;
        }
        if (!the_enemy)
        {
                finish_biwu(); 
                return;
        }
        the_id = all_npc[num]["id"];
        if (the_id == the_enemy->query("id"))
        {
                paiming--;
                do_biwu(paiming);
                return;
        }
        ob = new(GAOSHOU_OBJ);
        ob->move(BIWU_ROOM);
        the_npc = ob;
}

int csh_paiming()
{
        int i;
        string *str,*line;
        mapping per_paiming;

        if (file_size(GAOSHOU_DIR + "list")<0)
                return 0;
        str = explode(read_file(GAOSHOU_DIR + "list"),"\n");
        //if (sizeof(str) != 10)
                //return 0;
        all_npc = ([]);
        for (i = 0;i < sizeof(str);i ++)
        {
                per_paiming = ([]);
                line = explode(str[i],"|");
                if (sizeof(line) != 2) return 0;
                per_paiming["id"] = line[0];
                per_paiming["title"] = line[1];
                all_npc += ([ i : per_paiming ]);
        }
        the_enemy = 0;
        the_npc = 0;
        the_id = "";
        tmp_map = ([]);
        return 1;
}

void save_paiming()
{
        int i;
        string str;
        str = "";
        for (i = 0;i < sizeof(all_npc);i ++)
        {
                str += all_npc[i]["id"] + "|" + all_npc[i]["title"];
                if (i + 1 != sizeof(all_npc))
                        str += "\n";
        }
        write_file(GAOSHOU_DIR + "list",str,1);
        return;
}

void npc_lost()
{
        paiming--;
        do_biwu(paiming);
}

void finish_biwu()
{
        int i,j;
        int mingci,old_mingci;
        string from_file,to_file,temp_file;
        string weapon_file,armor_file,*carry_ob;
        object weapon,armor,temp_ob;

        if (can_biwu)
        {
                csh_paiming();
                return;
        }

        can_biwu = 1;

        if (!objectp(the_enemy))
                return;

        mingci = paiming + 1;

        if (mingci > 5)
                return;

        old_mingci = 100;
        for (i = 0;i < sizeof(all_npc);i++)
        {
                if (all_npc[i]["id"] == the_enemy->query("id"))
                {
                        old_mingci = i;
                        break;
                }
        }
        if (old_mingci == 100)
                old_mingci = 5;
        else if (mingci >= old_mingci)
                return;

        if (living(the_enemy) && base_name(environment(the_enemy)) == BIWU_ROOM)
                message_vision(HIW"$N����һЦ������Ʈ������̨��\n"NOR,the_enemy);

        if (old_mingci == 5)
        {
                //ɾ�������µ�ʮ������
                temp_file = GAOSHOU_DIR + "npc/" + all_npc[5]["id"] + ".o";
                if (file_size(temp_file) >= 0)
                        rm(temp_file);
                temp_file = GAOSHOU_DIR + "npc/" + all_npc[5]["id"] + "-weapon.c";
                if (file_size(temp_file) >= 0)
                        rm(temp_file);
                for (i = 0;i < sizeof(armor_type);i++)
                {
                        temp_file = GAOSHOU_DIR + "npc/" + all_npc[5]["id"] + "-" + armor_type[i] + ".c";
                        if (file_size(temp_file) >= 0)
                                rm(temp_file);
                }
        }

        carry_ob = ({});
        from_file = the_enemy->query_save_file() + ".o";
        to_file = GAOSHOU_DIR + "npc/" + the_enemy->query("id") + ".o";
        for (i = old_mingci;i >= 0;i--)
        {
                if (i < mingci) break;
                if (i == mingci)
                {
                        all_npc[i] = tmp_map;
                        //������ҵ���
                        cp(from_file,to_file);

                        //�޸��µĵ�������
                        temp_ob = new(TEMP_OBJ);
                        temp_ob->delete_status();
                        //��������
                        if (objectp(weapon = the_enemy->query_temp("weapon")) &&
			    (!weapon->is_no_clone() ||
                             weapon->is_item_make()))
                        {
                                weapon_file = base_name(weapon);
                                if (strlen(weapon_file) > 11 && 
                                    weapon_file[0..10] == "/data/item/")
                                {
                                        from_file = weapon_file + ".c";
                                        to_file = GAOSHOU_DIR + "weapon/" + 
                                                  the_enemy->query("id") + 
                                                  "-weapon.c";
                                        cp(from_file,to_file);
                                        temp_ob->set("can_summon/" + the_enemy->query("id") + 
                                                     "-weapon",to_file);
                                } else carry_ob += ({ weapon_file });
                        }

                        //���Ʒ���
                        for (j = 0;j<sizeof(armor_type);j++)
                        {
                                if (objectp(armor = the_enemy->query_temp("armor/"+armor_type[j])))
                                {
                                        armor_file = base_name(armor);
                                        if (strlen(armor_file) > 11 && 
                                            armor_file[0..10] == "/data/item/")
                                        {
                                                from_file = armor_file + ".c";
                                                to_file = GAOSHOU_DIR + "weapon/" + 
                                                          the_enemy->query("id") + 
                                                          "-" + armor_type[j] + ".c";
                                                cp(from_file,to_file);
                                                temp_ob->set("can_summon/" + the_enemy->query("id") + 
                                                             "-" + armor_type[j],to_file);
                                        } else carry_ob += ({ armor_file });
                                }
                        }
                        
                        if (sizeof(carry_ob))
                                temp_ob->set("carry_ob",carry_ob);

                        temp_ob->set("auto_perform",1);
                        temp_ob->save();
                        destruct(temp_ob);
                        break;
                }
                all_npc[i] = all_npc[i - 1];
        }
        save_paiming();
        message("sys",HIW + "�����������" + NOR + HIY + "��ϲ" + the_enemy->name(1) +
                               "�ٵ�" + HIG + "���µ�" + chinese_number(mingci + 1) +
                               NOR + HIY + "�ı�����\n" + NOR,all_interactive());

        csh_paiming();
        return;
}

mixed *get_the_dir(string dir)
{
        return get_dir(dir);
}
