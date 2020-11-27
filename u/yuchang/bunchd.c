// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// bunchd.c

#include <ansi.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// �������������10��
#define MAX_BUNCH_FAME         1000000000

// ÿ�����������100������
#define MAX_HATRED_PERSON       100

// �����˳�����ʱ��ÿ���Ƴ����ٸ�
#define HATREDP_REMOVED         10
#define BUNCH_HOME              "/data/bunch/"
#define RM_CMD                  "/cmds/wiz/rm"
#define CP_CMD                  "/cmds/wiz/cp"

mapping bunch_fame;
mapping last_bunch_fame;

// area's base_name & short
mapping area_fame;

// ���ɶԳ��˳�޶ȵ�����
private int sort_hatred(string id1, string id2, mapping hatred);
public mixed check_areas();
public void dismiss_bunch(string fname);
public mixed query_all_areas() { return area_fame; }
public int end_bunch_war(string wname, string lname, int gold);
public int war_stop_time(string fname);
public int bunch_is_league(mixed ob1, mixed ob2);

nosave string *npc_bunch = ({
        "�ڰ׵�",
        "������",
        "С����",
        "������",
        "�޼���",
        "������",
});

nosave string *bad_weather = ({
        "�ܸɺ���Ӱ�죬$N����",
        "���ڱ���Ϯ����$N�ճɵ���",
        "$N�⵽�����ܵ�Ϯ��������",
        "�ٸ����ض�$N����˰��$N����",
        "������$N��Ű����ʧ����",
        "�����Ϯ����$N�������ɾ޴���ʧ",
        "$N������������Ա�������أ���ʧ",
        "$Nͻ��������Ա�������أ����Ѿ޴�",
});

nosave mapping citys = ([
        "bj"  : "������",
        "yz"  : "���ݳ�",
        "ca"  : "������",
        "cd"  : "�ɶ���",
        "sz"  : "���ݳ�",
        "hz"  : "���ݳ�",
        "xy"  : "������",
        "dl"  : "�����",
]);

void create()
{
        mapping data;

        seteuid(getuid());
        restore();
        set_heart_beat(3600); // ����Сʱ
        if (! mapp(bunch_fame)) bunch_fame = ([ ]);
        if (! mapp(area_fame)) area_fame = ([ ]);
}

void remove()
{
        save();
}
// Ҫ�� CMDS:REBOOT ������ϵ���
public void mud_shutdown()
{
        save();
}

// ������ά�����ɵ�ͨ����Ϣ
private void heart_beat()
{
        int t;
        int last;
        string *all_fam;
        string fam;

        t = time();
        last = query("last_check");
        if ((t / 86400) != (last / 86400))
        {
                // ���������˱仯�����ư��ɵ�������Ϣ
                all_fam = keys(bunch_fame) - ({ 0 });
                last_bunch_fame = ([ ]);

                foreach (fam in all_fam)
                        last_bunch_fame[fam] = bunch_fame[fam];
        }
        set("last_check", t);
        all_fam = keys(bunch_fame) - ({ 0 });
        foreach (fam in all_fam)
        {
                if (query(fam + "/war_endtime") &&
                    time() > query(fam + "/war_endtime"))
                        war_stop_time(fam);
        }

        // �����������̵㴦��
        check_areas();

        // ������ɵ�������Ϣ
        save();
}

public mixed check_areas()
{
        string  bunch_name, bad_area, *item, *all_area,
                *all_bunch, *lost, str;
        object  room, player, npc;
        int     weiwang, jizhi, kaifa, zhongcheng, count, i;
        int     area_money, bad_money, rest_money, npc_money, cost;
        mapping data = ([ ]);

        all_area = keys(area_fame) - ({ 0 });

        if (! arrayp(all_area) || ! sizeof(all_area))
                return;

        if (random(sizeof(all_area)) > 10)
        {
                bad_area = all_area[random(sizeof(all_area))];

                if (undefinedp(area_fame[bad_area]["ziyuan"]))
                        bad_area = "";
        }
        else
                bad_area = "";

        foreach (string area in all_area)
        {
                reset_eval_cost();

                bunch_name = area_fame[area]["bunch_name"];

                if (bunch_name == "������")
                        continue;

                if (! (room = get_object(area)))
                        continue;

                // �̵�ʱ����� NPC ����ʱ����������
                if (undefinedp(area_fame[area]["npc_id"]) ||
                    ! objectp(npc = present(area_fame[area]["npc_id"], room)))
                        continue;

                if (! mapp(query(bunch_name)))
                {
                        message("channel:rumor", HIM"���л���᡿���ڰ����߽⣬" +
                                room->query("short") + "����������" + "��" + bunch_name +
                                "��" + "�Ŀ��ƣ�\n" NOR, users());

                        npc->delete("bunch");
                        area_fame[area]["bunch_name"] = "������";
                        continue;
                }
#ifdef LONELY_IMPROVED
                if (count_lt(area_fame[area]["money"], -1000000) ||
                    count_lt(query(bunch_name + "/money"), -100000000))
#else
                if (area_fame[area]["money"] < -1000000 ||
                    query(bunch_name + "/money") < -100000000)
#endif
                {
                        message("channel:rumor", HIM"���л���᡿���ھ�Ӫ���ƣ�" +
                                room->query("short") + "����������" + "��" + bunch_name +
                                "��" + "�Ŀ��ƣ�\n" NOR, users());

                        // ������������
                        weiwang = bunch_fame[bunch_name];
                        weiwang -= 1000;
                        if (weiwang < 0) weiwang = 0;
                        bunch_fame[bunch_name] = weiwang;

                        npc->delete("bunch");
                        area_fame[area]["bunch_name"] = "������";
                        continue;
                }

                zhongcheng = area_fame[area]["zhongcheng"];
                if (! intp(zhongcheng) || zhongcheng < 10)
                        zhongcheng = 10;

                zhongcheng -= random(2);

                if (zhongcheng >= 100)
                        zhongcheng = 100;

                npc->set("bunch/zhongcheng", zhongcheng < 10 ? 10 : zhongcheng);
                area_fame[area]["zhongcheng"] = (zhongcheng < 10 ? 10 : zhongcheng);

                jizhi = area_fame[area]["jizhi"];
                kaifa = area_fame[area]["kaifa"];
                jizhi += random(2);
                kaifa -= random(2);

                area_money = area_fame[area]["money"];
                if (! stringp(area_money) && ! intp(area_money))
                        area_money = 0;

                if (! intp(jizhi) || jizhi < 6)
                        jizhi = 6;
                else if (jizhi > 60)
                        jizhi = 60;

                if (! intp(kaifa) || kaifa < 20)
                        kaifa = 20;
                else if (kaifa > 100)
                        kaifa = 100;

                area_fame[area]["kaifa"] = kaifa;
                area_fame[area]["jizhi"] = jizhi;

                if (area == bad_area)
                {
                        if (jizhi && kaifa < 80)
                        {
                                bad_money = kaifa * jizhi * 1000;
                                area_money -= bad_money;
                        } else
                        { // �����ȸߵģ�һ����˵��Ȼ�ֺ�Ӱ�첻��
                                bad_area = "";
                                area_money += (kaifa / 2) * (jizhi / 2) * 100;
                        }
                } else
                        area_money += (kaifa / 2) * (jizhi / 2) * 200;

                rest_money = area_money - 1000000;
                if (rest_money < 0)
                        rest_money = 0;

                area_fame[area]["money"] = area_money - rest_money;
                area_fame[area]["last_money"] = rest_money;

                data[bunch_name] += rest_money;
        }

        all_bunch = keys(bunch_fame);

        if (! arrayp(all_bunch) || ! sizeof(all_bunch))
                return;

        lost = ({ });
        foreach (string bunch in all_bunch)
        {
                reset_eval_cost();

                npc_money = query(bunch + "/npc_money");
                set(bunch + "/last_npc_money", npc_money);
                set(bunch + "/npc_money", 0);

                set(bunch + "/last_area_money", data[bunch]);

                data[bunch] += npc_money;
                if (data[bunch] < 0) data[bunch] = 0;

                data[bunch] /= 2;
#ifdef LONELY_IMPROVED
                set(bunch + "/money", count_add(query(bunch + "/money"), data[bunch]));
#else
                if (query(bunch + "/money") < 2000000000)
                        add(bunch + "/money", data[bunch]);
#endif
                cost = 200 * (sizeof(BUNCH_D->query_bunch_areas(bunch)) * 2 +
                              sizeof(query(bunch + "/member")));

#ifdef LONELY_IMPROVED
                set(bunch + "/money", count_sub(query(bunch + "/money"), cost));
#else
                add(bunch + "/money", -cost);
#endif
                data[bunch] /= 2;

                add(bunch + "/bangzhu_money", data[bunch]);
                set(bunch + "/last_bangzhu_money", data[bunch]);

#ifdef LONELY_IMPROVED
                if (count_lt(query(bunch + "/money"), -100000000))
#else
                if (query(bunch + "/money") < -100000000)
#endif
                {
                        message("channel:rumor", HIW "���л���᡿���ڰ����ʲ��������ؿ��𣬰�ᡸ" +
                                                 bunch + "���޷�ά���ճ���֧�������߽��ˣ�\n" NOR, users());
                        lost += ({ bunch });
                        map_delete(data, bunch);
                }
        }

        if (arrayp(lost) && sizeof(lost) > 0)
        {
                foreach (bunch_name in lost)
                        dismiss_bunch(bunch_name);
        }
        lost = ({ });

        if (! arrayp(users()) || ! sizeof(users()))
                return;

        // give all online player banghui's money
        item = keys(data);

        for (i = 0; i < sizeof(item); i++)
        {
                reset_eval_cost();

                count = 0;

                foreach (player in users())
                {
                        reset_eval_cost();

                        if (! playerp(player)) continue;

                        if (! player->query("bunch/bunch_name") ||
                            player->query("bunch/bunch_name") != item[i])
                                continue;

                        count++;
                }

                if (count == 0) count = 1;
                data[item[i]] /= count;
        }

        foreach (player in users())
        {
                reset_eval_cost();

                if (! playerp(player)) continue;

                if (! player->query("bunch/bunch_name")) continue;

                if (! data[player->query("bunch/bunch_name")]) continue;

                tell_object(player, HIG "���ɡ�" + player->query("bunch/bunch_name") + "��" + "���ã���Ĵ��������" +
                                    MONEY_D->money_str(data[player->query("bunch/bunch_name")]) + "��\n" NOR);

#ifndef LONELY_IMPROVED
                if ((int)player->query("balance") > 2000000000)
                        tell_object(player, RED "����Ǯׯ��Ǯ�Ѵﵽ��ʮ�����ƽ𣬿�㻨�ɣ�\n" NOR);
                else
#endif
                        player->add("balance", data[player->query("bunch/bunch_name")]);
        }

        if (bad_area == "")
                message("channel:rumor", HIM "�������̵㡿ĳ�ˣ��������������ã����λ��������Ǯׯת�ʣ�\n" NOR,
                        users());
        else
        {
                str = bad_weather[random(sizeof(bad_weather))];
                str = replace_string(str, "$N", bad_area);

                message("channel:rumor", HIM "�������̵㡿ĳ�ˣ�" + str +
                                         MONEY_D->money_str(bad_money) + "��\n" NOR, users());
        }
        save();
}

// ���ذ����������������Ϊ�գ�����mapping���ͣ�����������ͬ
// �˵������������������� �򷵻ظ��������ڵ��Ǹ����ɵ���
// ������������ǰ��ɣ��򷵻ظð��ɵ�������
public mixed query_bunch_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return bunch_fame[ob];

        if (objectp(ob))
        {
                if (stringp(fname = ob->query("bunch/bunch_name")))
                        return bunch_fame[fname];
                else
                        return 0;
        }

        return bunch_fame;
}

// ��ѯ����İ���������Ϣ
public mapping query_all_last_bunch_fame()
{
        if (! mapp(last_bunch_fame))
                // û���������Ϣ�����ؽ����
                return bunch_fame;

        // ��������İ���������Ϣ
        return last_bunch_fame;
}

// ��ѯ���ɵĳ����Ϣ�������ob�����ǰ��ɵ����֣�Ҳ����
// �е����
public mapping query_bunch_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
                return 0;

        return hatred;
}

// �仯���������������ob�����ǰ��ɵ����֣�Ҳ���ǰ����е����
public void add_bunch_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(query(fname + "/member")))
                return;

        // �����µİ�������
        new_fame = bunch_fame[fname] + n;
        if (new_fame < 0) new_fame = 0;
        if (new_fame > MAX_BUNCH_FAME)
                new_fame = MAX_BUNCH_FAME;
        bunch_fame[fname] = new_fame;
}

// ���ɼ��ɱ
public void bunch_kill(object killer, object victim)
{
        int kexp;
        int vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // ֻ�����֮��ĳ�ɱ�ż�������
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // ��ʦ֮��ıȻ��ɲ�������
        if (wizardp(killer) || wizardp(victim))
                return;

        // �鿴��������������İ���
        kfam = killer->query("bunch/bunch_name");
        vfam = victim->query("bunch/bunch_name");

        if (! stringp(kfam) && ! stringp(vfam))
                // �����ڰ����ڣ����ؼ�����
                return;

        kexp = killer->query("combat_exp");
        vexp = victim->query("combat_exp");

        if (kfam == vfam)
        {
                if (! killer->is_killing(victim->query("id")))
                        // ʧ����ɱ���������
                        return;

                // �����ڲ�ɱ��������ᣬֱ�ӿ۳����ɺ͸���1/10������
                add_bunch_fame(kfam, -bunch_fame[kfam] / 10);
                killer->add("weiwang", -killer->query("weiwang") / 10);
                return;
        } else
        if (bunch_is_league(kfam, vfam))
        {
                if (! killer->is_killing(victim->query("id")))
                        // ʧ����ɱ���������
                        return;
                // ͬ�˰����ڲ�ɱ��ֱ�ӿ۳����ɺ͸���1/20������
                add_bunch_fame(kfam, -bunch_fame[kfam] / 20);
                killer->add("weiwang", -killer->query("weiwang") / 20);
                return;
        }

        if (kexp < vexp * 3 && vexp >= 100000)
        {
                // ɱ�ֵľ��鲻��ԶԶ�Ĵ��ڶԷ������ұ�ɱ��
                // ����һ���ľ��飬�⽫���°��������Ľ��͡�
                fame_delta = vexp + killer->query("score") * 2 +
                             killer->query("weiwang") * 10;
                fame_delta /= 1000;
        } else
                // ���־���̫�٣����ǲ��̫�󣬲�Ӱ������
                fame_delta = 0;

        // �鿴ɱ�����ڵİ����Ƿ������ߣ������ޣ����ܹ�
        // ���������ı仯��
        if (stringp(kfam))
        {
                string path;

                path = kfam + "/hatred/"+ victim->query("id");
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // ������ߣ����ɻ�ö��������
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "��˵" + killer->name(1) + "������" +
                                        victim->name(1) + "��Ϊ" +
                                        kfam + "����һ�ڶ�����");
                        fame_delta += d[1] / 3;

                        // �Դ��˵ĳ�޽���(���͵�Ҫ�����ӵ�Ҫ��)��
                        // ������Կ�fame_delta ���޶ȹ�˾�Ĳ���
                        d[1] -= fame_delta;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // �����������ɵ�����
        add_bunch_fame(killer,  fame_delta);
        add_bunch_fame(victim, -fame_delta);

        // ͳ�Ƹ�ɱ�ֶԱ��ŵĲк��̶�
        if (! stringp(vfam))
                return;

        // ��޳̶Ⱥ������ı仯������һ����������(K����)����
        // �ǳ�޳̶ȵ��������ı仯��
        vexp = vexp / 1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid = killer->query("id");
        if (! mapp(hatred = query(vfam + "/hatred")))
        {
                set(vfam + "/hatred/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // ÿ����������¼���ɸ�����
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // ���ID�����ݳ��˹���
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // ����ȥ��һЩ�ˣ�Ϊʲô��ȥ��һ��������Ϊ
                // �˷�ֹ����Ƶ���Ľ��й��˲�����
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // ��¼����˵���Ϣ
        hatred[kid] = d;
}

// ȥ�����а��ɶ�ĳ���˵ĳ����Ϣ
public void remove_hatred(string id)
{
        mapping dbase, bunch, hatred;
        string fam;

        if (! mapp(dbase = query_entire_dbase()))
                // ���ڻ�û�г����Ϣ
                return;

        // �������е�
        foreach (fam in keys(dbase))
        {
                reset_eval_cost();

                if (! mapp(bunch = dbase[fam]))
                        continue;

                if (mapp(hatred = bunch["hatred"]))
                        // ȥ���ð��ɶ�ĳ�˵ĳ����Ϣ
                        map_delete(hatred, id);

                if (! mapp(hatred) || sizeof(hatred) < 1)
                        // ��������Ѿ�û�г����Ϣ
                        map_delete(bunch, "hatred");
        }

        save();
}

public mixed valid_new_build(object ob, string id, string name)
{
        object env;

        if (! env = environment(ob))
                return "��������˵����⣬�����ʦ��ϵ��\n";

        if (! env->is_create_bunch_room())
                return "���ﲻ�����������������̳������ѡ�ص㡣\n";

        if (env->query_room_id(id) || env->query_room_name(name))
                return "�����Ѿ��и�����ʹ������������ˡ�\n";

        if (file_size(BUNCH_HOME + id + "/center.c") > 0)
                return "�Ѿ��б�İ���ʹ�������ID�����ˡ�\n";
        // ......
        return 0;
}

// �鿴�Ƿ���Դ������
public mixed valid_new_bunch(string fname)
{
        if (query(fname + "/member"))
                return "�˼�����н������������ͱ�������ˡ�\n";

        if (member_array(fname, npc_bunch) != -1)
                return "��������������ֳɵİ��ɣ��㻹����ʲô��\n";

        if (! undefinedp(FAMILY_D->query_family_fame(fname))
                || ! undefinedp(LEAGUE_D->query_league_fame(fname)))
                return "�������Ѿ���" + fname + "�ˣ��㻹����ʲô��\n";

        return 0;
}

// ��������
public void create_bunch(string fname, string id, string type, int base, object *obs)
{
        mapping data;
        string *channels;
        string master, zone, entry, center, quester;
        object ob, env, creater;
        string code, city, position;

        bunch_fame[fname] = base;
        if (! mapp(last_bunch_fame))
                last_bunch_fame = ([ fname : base ]);
        else
                last_bunch_fame[fname] = base;

        foreach (ob in obs)
        {
                data = ([ "time"  : time(),
                          "bunch_name"  : fname,
                          "bunch_id"  : id,
                          "type"  : type  ]);

                if (ob->is_team_leader())
                {
                        creater = ob;
                        master = ob->query("id");
                        position = base_name(env = environment(ob));
                        zone = domain_file(position);

                        data += ([ "level" : 9,
                                   "title" : "����" ]);
                } else
                {
                        data += ([ "level" : 1,
                                   "title" : "����" ]);
                }

                ob->set("bunch", data);

                channels = ob->query("channels");
                if (! arrayp(channels) || ! sizeof(channels))
                        channels = ({ "party" });
                else
                if (member_array("bunch", channels) == -1)
                        channels += ({ "party" });

                ob->set("channels", channels);
                ob->save();
        }

        quester = BUNCH_HOME + id + "/npc/quester.c";
        assure_file(quester);

        switch(zone)
        {
                case "beijing": city = "bj"; break;
                case "city": city = "yz";  break;
                case "changan": city = "ca"; break;
                case "city3": city = "cd"; break;
                case "suzhou": city = "sz"; break;
                case "hangzhou": city = "hz"; break;
                case "xiangyang": city = "xy"; break;
                case "dali": city = "dl"; break;
                default: city = "yz"; break;
        }

        code = @CODE
// Create by BUNCH_D written by Lonely
// quester.c

#include <ansi.h>
inherit NPC;
CODE;
        code += "#define PLACE          \"" + city + "\"\n";
        code += "#define TYPE           \"" + type + "\"\n";
        code += "#define WAIT_TIME      60\n\n";

        if (type == "bad")
        {
                code += sprintf("mapping bunch_bad = ([\n\t\"bunch_name\" : \"%s\",\n\t\"id\" : \"%s\",\n\t" +
                                "\"place\" : \"%s\",\n\t\"boss\" : \"%s\",\n\t\"place_name\" : \"%s\",\n\t" +
                                "\"type\"  : \"%s\",\n\t]);\n", fname, id,
                                city, creater->name(), citys[city], type);
        } else
        {
                code += sprintf("mapping bunch_good = ([\n\t\"bunch_name\" : \"%s\",\n\t\"id\" : \"%s\",\n\t" +
                                "\"place\" : \"%s\",\n\t\"boss\" : \"%s\",\n\t\"place_name\" : \"%s\",\n\t" +
                                "\"type\"  : \"%s\",\n\t]);\n", fname, id,
                                city, creater->name(), citys[city], type);
        }
        code += @CODE

void create()
{
        set_name("����ʹ��", ({ "quester" }));
        set("gender", "����");
        set("age", 23);
        set("long", "����һ�����ú�Ӣ�������ӣ�����ȥ�������Ρ�\n");
CODE;
        if (type == "bad")
        {
                code += @CODE
        set("bunch/bunch_name", bunch_bad["bunch_name"]);
        set("shen_type", -1);
CODE;
        } else
        {
                code += @CODE
        set("bunch/bunch_name", bunch_good["bunch_name"]);
        set("shen_type", 1);
CODE;
        }
        code += @CODE
        set("per", 29);
        set("combat_exp", 1000000);

        set("attitude", "peaceful");

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 2);
}

CODE;
        if (type == "bad")
                code += "#include <boss_bad.h>\n";
        else
                code += "#include <boss_good.h>\n";

        write_file(quester, code, 1);

        center = BUNCH_HOME + id + "/center.c";
        assure_file(center);

        code = @CODE
// Create by BUNCH_D written by Lonely
// center.c

#include <ansi.h>
#include <room.h>
inherit ROOM;
CODE;
        code += "#define PLACE   \"" + city + "\"\n";
        code += "#define TYPE    \"" + type + "\"\n";

        code += @CODE

// int is_bunch_room() { return 1; }
int sort_by_id(mapping quest1, mapping quest2);

void create()
{
CODE;
        code += sprintf("\tset(\"short\", \"%s��̳\");\n", fname);

        code += sprintf("\tset(\"long\", \"�����ǽ����һ������(paizi)���������" +
                        "%s����ң�����������ѡ������ȥ��ɡ�\\n\");\n", fname);

        code += "\tset(\"objects\", ([\n\t\t__DIR__\"npc/quester\" : 1,\n\t]));\n";
        code += "\tset(\"exits\", ([\n\t\t\"south\" : __DIR__\"room9\", \n\t]));\n";
        code += "\n\tsetup();\n}\n\n";
        // code += "\treplace_program(ROOM);\n}\n";
        code += sprintf("#include <bang_%s.h>\n", type);

        write_file(center, code, 1);

        entry = BUNCH_HOME + id + "/entry.c";
        assure_file(entry);

        code = @CODE
// Create by BUNCH_D written by Lonely
// entry.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_bunch_room() { return 1; }

void create()
{
	set("short", "�շ��� - ��ʹ�� cshort ���༭����");
	set("long", "����һ��ʲôҲû�еĿշ��䣬������ clong ���༭����������\n");

        set("exits", ([
                "north" : __DIR__"room0",
CODE;
        code += sprintf("\t\t\"out\" : \"%s\", \n\t]));\n", base_name(env));
        code += "\n\tsetup();\n}\n\n";

        write_file(entry, code, 1);

        env->create_room(fname, id, entry);

        CP_CMD->copy_dir("/d/room/bunch/", BUNCH_HOME + id + "/");

        message("vision", creater->name() + "����һ�ѹ�������" + env->query("short") +
                "���ô��ģ������һЩ���䡣\n", env);

        data = ([
                "bunch_id"      : id,                // ���ɴ���
                "bunch_name"    : fname,             // ��������
                "time"          : time(),            // ���ɳ���ʱ��
                "master"        : master,            // ���ɰ���
                "color"         : NOR,               // ������ɫ
                "money"         : 10000000,          // �����ʽ�
                "member"        : obs->query("id"),  // ���ɳ�Ա
                "type"          : type,              // ������а
                "tax"           : 5,                 // ����˰��
                "alert"         : 0,                 // ���ɾ���(1~4)
                "league"        : ({}),              // ����ͬ��
                "char_status"   : 0,                 // �����˲�
                "weapon_status" : 0,                 // ��������
                "char_money"    : 0,                 // Ͷ�����˲ĵĽ��
                "weapon_money"  : 0,                 // Ͷ���������Ľ��
                "senior"        : obs->query("id"),  // Ԫ�ϣ�����������
                "room_position" : position,          // ���������ļ�·��
                "room_entry"    : entry,             // ��������ļ�·��
                "room_name"     : fname,             // ������ڴ�������
                "room_id"       : id,                // ������ڷ������
                "room_zone"     : zone,              // ��������λ������
                "war_target"    : "NULL",            // ����ս���ж԰���
                "war_kill"      : 0,                 // ս��ɱ����������
                "war_endtime"   : 0,                 // ����ս������ʱ��
                "war_win"       : 0,                 // ����ս��ʤ������
                "war_lose"      : 0,                 // ����ս��ʧ�ܴ���
        ]);
        set(fname, data);

        save();
}

// ��ɢ����
public void dismiss_bunch(string fname)
{
        string *ids;
        string id, dir, pos;
        object ob, npc, room;

        // ���������Ϣ
        map_delete(bunch_fame, fname);
        if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

        // ��������е�������ҵ������Ϣ
        ids = query(fname + "/member");
        dir = query(fname + "/room_id");
        pos = query(fname + "/room_position");

        if (arrayp(ids))
        {
                // �����л�����ң�������ǵ���Ϣ
                foreach (id in ids)
                {
                        // ������
                        reset_eval_cost();
                        UPDATE_D->clear_user_data(id, "bunch");
                }
        }

        ids = BUNCH_D->query_bunch_areas(fname);

        if (arrayp(ids))
        {
                // �����л��е��̣�������ǵ���Ϣ
                foreach (id in ids)
                {
                        // ������
                        reset_eval_cost();
                        area_fame[id]["bunch_name"] = "������";

                        ob = get_object(id);
                        if (! ob) continue;

                        if (objectp(npc = present(area_fame[id]["npc_id"], ob)))
                                npc->delete("bunch");
                }
        }

        RM_CMD->rm_dir(BUNCH_HOME + dir);

        if (stringp(pos))
        {
                room = get_object(pos);
                if (objectp(room))
                {
                        message("vision", "ͻȻ����ͯ�ӷ�Ҳ��"
                                  "�ĳ��˹�����������Ÿ��ּһ�"
                                  "�����µ�����������������\n",
                                  room);
                        room->destroy_room(dir);
                        room->save();
                }
        }

        // ������ɵ�������Ϣ
        delete(fname);
        save();
}

// ��ѯ�����еĵ���
public string *query_bunch_members(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/member")))
                return 0;

        return member;
}

// ��ѯ�����еĵ���
public string *query_bunch_areas(mixed ob)
{
        string *areas, *aname;
        string fname, afile;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        aname = keys(area_fame);
        areas = ({ });
        foreach (afile in aname)
        {
                if (area_fame[afile]["bunch_name"] == fname)
                        areas += ({ afile });
        }

        return areas;
}

public string *query_bunch_league(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/league")))
                return 0;

        return member;
}

// ��ѯ���̵���Ϣ
public mixed query_area_info(string afile, string info)
{
        if (! stringp(afile) || ! stringp(info))
                return 0;

        if (! mapp(area_fame) || ! sizeof(area_fame))
                return 0;

        if (undefinedp(area_fame[afile]))
                return 0;

        if (info == "dbase")
                return area_fame[afile];

        return area_fame[afile][info];
}

// ��ѯ���ɵ���Ϣ
public mixed query_bunch_info(string fname, string info)
{
        if (stringp(fname) && stringp(info))
        {
                if (info == "dbase")
                        return query(fname);

                return query(fname + "/" + info);
        }
        else
                return 0;
}

// �ڰ����б䶯������������������ʲ��������ȡ�
public void add_bunch_info(string fname, string info, mixed n)
{
        if (! mapp(query(fname)))
                return;

        if (intp(n))
                add(fname + "/" + info, n);
        else
        if (stringp(n))
                set(fname + "/" + info, n);
        else
                set(fname + "/" + info, n);
}

// �ı�����еĲ���ֵ
public void add_area_info(string afile, string info, mixed value)
{
        if (undefinedp(area_fame[afile]))
                return;

        if (intp(value))
                area_fame[afile][info] += value;
        else
        if (stringp(value))
                area_fame[afile][info] = value;
        else
                area_fame[afile][info] = value;
}

public void set_area_info(string afile, string info, mixed value)
{
        if (undefinedp(area_fame[afile]))
                return;

        area_fame[afile][info] = value;
}

public void remove_area_from_areas(string area_file)
{
        map_delete(area_fame, area_file);
}

// �Ӱ�����ȥ��һ����
public varargs void remove_member_from_bunch(mixed fname, string id)
{
        mapping bunch;
        string *member;
        string *areas;
        string area;
        object room, npc;
        string dir, pos;

        if (objectp(fname))
        {
                // fname is user object
                id = fname->query("id");
                if (! stringp(fname = fname->query("bunch/bunch_name")))
                        return;
        } else
        if (! stringp(fname))
                // or fname must be a bunch name
                return;

        if (! mapp(bunch = query(fname)) ||
            ! arrayp(member = bunch["member"]))
                // no such bunch or no member in the
                return 0;

        member -= ({ id, 0 });
        if (sizeof(member) < 1)
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + fname + "�˲ŵ��㣬���հ��ھ���ɢȥ���Ӵ˽������޴˰����ˡ�");

                map_delete(bunch_fame, fname);
                if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

                dir = query(fname + "/room_id");
                pos = query(fname + "/room_position");
                areas = BUNCH_D->query_bunch_areas(fname);

                if (arrayp(areas))
                {
                        // �����л��е��̣�������ǵ���Ϣ
                        foreach (area in areas)
                        {
                                // ������
                                reset_eval_cost();
                                area_fame[area]["bunch_name"] = "������";

                                room = get_object(area);
                                if (! room) continue;

                                if (objectp(npc = present(area_fame[area]["npc_id"], room)))
                                        npc->delete("bunch/bunch_name");
                        }
                }

                RM_CMD->rm_dir(BUNCH_HOME + dir);

                if (stringp(pos))
                {
                        room = get_object(pos);
                        if (objectp(room))
                        {
                                message("vision", "ͻȻ����ͯ�ӷ�Ҳ��"
                                        "�ĳ��˹�����������Ÿ��ּһ�"
                                        "�����µ�����������������\n",
                                        room);
                                room->destroy_room(dir);
                                room->save();
                        }
                }

                delete(fname);
        } else
                bunch["member"] = member;
}

// �ڰ���������һ����
public void add_member_into_bunch(string fname, string id)
{
        string *member;

        if (! arrayp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, member) != -1)
                return 0;

        member += ({ id });
        set(fname + "/member", member);
        save();
}

// ���ӵ��̵����ɿ�����
public void add_area_into_bunch(string fname, string afile, string aname, object ob)
{
        string bname;
        mapping data;
        string *areas;

        areas = keys(area_fame);
        if (member_array(afile, areas) == -1)
        {
                data = ([
                        "area_name"  : aname,
                        "bunch_name" : fname,
                        "npc_id"     : ob->query("id"),
                        "npc_name"   : ob->query("name"),
                        "kaifa"      : 10,
                        "zijin"      : 10,
                        "zhongcheng" : 10,
                        "money"      : 0,
                        "last_money" : 0,
                ]);

                area_fame[afile] = data;
        } else
        {
                bname = area_fame[afile]["bunch_name"];
                if (bname != "������")
                        message("channel:rumor",  HIM "�����ɴ��š�ĳ�ˣ�" + aname +
                                "����������ɡ�" + bname + "���Ŀ��ƣ�\n" NOR, users());
                area_fame[afile]["bunch_name"] = fname;
                area_fame[afile]["zhongcheng"] = 10;
        }

        ob->set("bunch/bunch_name", fname);
        ob->set("bunch/zhongcheng", 10);
        ob->set("bunch/max_zhongcheng", 100);

        message("channel:rumor", HIM "�����ɴ��š�ĳ�ˣ�" + ob->query("name") +
                "������ɡ�" + fname + "����\n" NOR, users());

        message("channel:rumor", HIM "�����ɴ��š�ĳ�ˣ�" + aname +
                "�����ɡ�" + fname + "���̲���\n" NOR, users());

        return;
}

// ��ѯ���������Ƿ�Ϊͬ��
public int bunch_is_league(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1 = ob1->query("bunch/bunch_name");

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2 = ob2->query("bunch/bunch_name");

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        foreach (string bun in lea)
                if (bun = bun2)
                        return 1;

        return 0;
}

// ����һ��ͬ�˰���
public int add_league_into_bunch(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1 = ob1->query("bunch/bunch_name");

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2 = ob2->query("bunch/bunch_name");

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea))
                lea = ({ bun2 });
        else
        if (member_array(bun2, lea) == -1)
                lea += ({ bun2 });

        set(bun1 + "/league", lea);

        lea = query(bun2 + "/league");

        if (! arrayp(lea))
                lea = ({ bun1 });
        else
        if (member_array(bun1, lea) == -1)
                lea += ({ bun1 });

        set(bun2 + "/league", lea);

        return 1;
}

// �Ƴ�һ��ͬ�˰���
public int remove_league_from_bunch(mixed ob1, mixed ob2)
{
        string *lea;
        string bun1, bun2;

        if (stringp(ob1)) bun1 = ob1;
        else
        if (objectp(ob1))
                bun1 = ob1->query("bunch/bunch_name");

        if (stringp(ob2)) bun2 = ob2;
        else
        if (objectp(ob2))
                bun2 = ob2->query("bunch/bunch_name");

        if (! stringp(bun1) || ! stringp(bun2))
                return 0;

        lea = query(bun1 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        if (member_array(bun2, lea) == -1)
                return 0;

        lea -= ({ bun2 });

        set(bun1 + "/league", lea);

        lea = query(bun2 + "/league");

        if (! arrayp(lea) || sizeof(lea) < 1)
                return 0;

        if (member_array(bun1, lea) == -1)
                return 0;

        lea -= ({ bun1 });

        set(bun2 + "/league", lea);

        return 1;
}

// ����ս��
public int announce_war_start(string fname, string bname)
{
        message("channel:rumor", HIR "\n\t�䶯���֡���������̡���\n\t"
                HIC + fname + HIR "��" HIM + bname + HIR "�İ���ì�ܼ�������ʼȫ�濪ս����\n" NOR, users());

        set(fname + "/war_target", bname);
        set(bname + "/war_target", fname);
        set(fname + "/war_endtime", time() + 3600);
        set(bname + "/war_endtime", time() + 3600);

        return 1;
}

public int war_stop_time(string fname)  // ��һ��ֹͣģʽ-ʱ�䵽
{
        int kill_1, kill_2, money;
        string bname, wname, lname;

        bname = query_bunch_info(fname, "war_target");

        kill_1 = query_bunch_info(fname, "war_kill");
        kill_2 = query_bunch_info(bname, "war_kill");

        if (kill_1 > kill_2)
        {
                wname = fname;
                lname = bname;
                money = kill_1 * 10000 + 100000;
        }
        else
        if (kill_1 < kill_2)
        {
                wname = bname;
                lname = fname;
                money = kill_2 * 10000 + 100000;
        }
        else
        {
                message("channel:rumor", HIR "\n\t�䶯���֡���������̡���\n\t"
                        HIC + fname + HIR "��" HIM + bname + HIR "�İ��ɶԾ����ڽ�������\n\t"
                        HIC + fname + HIR "�ܹ�ɱ��" HIM + bname + HIG " " + CHINESE_D->chinese_number(kill_1) + HIR "λ���ڣ�\n\t"
                        HIM + bname + HIC "�ܹ�ɱ��" HIC + fname + HIG " " + CHINESE_D->chinese_number(kill_2) + HIR "λ���ڣ�\n\t"
                        HIR + "˫�������˲��أ�����ƽ�����ա�\n" NOR, users());

                end_bunch_war(bname, fname, 0);

                return 1;
        }

        message("channel:rumor", HIR "\n\t�䶯���֡���������̡���\n\t"
                HIC + wname + HIR "��" HIM + lname + HIR "�İ��ɶԾ����ڽ�������\n\t"
                HIC + wname + HIR "�ܹ�ɱ��" HIM + lname + HIG " " + CHINESE_D->chinese_number(kill_1) + HIR "λ���ڣ�\n\t"
                HIM + lname + HIC "�ܹ�ɱ��" HIC + wname + HIG " " + CHINESE_D->chinese_number(kill_2) + HIR "λ���ڣ�\n\t"
                HIM + lname + HIC "ս�ܣ������⳥" HIC + wname + HIY " " +
                CHINESE_D->chinese_number(money) + HIR "���ƽ�\n" NOR, users());

                end_bunch_war(wname, lname, money);

                return 1;
}

public int war_stop_kill(string fname)   // �ڶ���ֹͣģʽ..����������......
{
        string bname, master;
        int number, money;

        bname = query_bunch_info(fname, "war_target");
        master = query_bunch_info(fname, "master");
        number = query_bunch_info(bname, "war_kill");
        money = number * 1000 + 100000;

        message("channel:rumor", HIC "\t����!!����!!�䶯���ֵ�" + HIG + bname + HIC "��" HIG + fname + HIC "�İ��ɶԾ��������˽����!!!!\n"
                HIG "       " + bname + HIC "ɱ����" HIG + fname + HIC "���ɰ���:" HIG + master + HIC "\n" +
                "\tһʱ֮��" + HIG + fname + HIC + "��Ϊ���������������¾��Ĵ���!!!һ·����!!!\n" + HIC +
                "\t����ж�::" + HIG + fname + HIC + "����Ҫ����" + CHINESE_D->chinese_number(money) + "�����⳥��!!!\n" NOR, users());


        end_bunch_war(bname, fname, money);
        return 1;
}

public int war_stop_money(string lname, int money)   // ������ֹͣģʽ..���......
{
        string wname, master;

        wname = query_bunch_info(lname, "war_target");
        master = query_bunch_info(lname, "master");

        message("channel:rumor", HIC "\t����!!����!!�䶯���ֵ�" + HIG + wname + HIC "��" + HIG + lname + HIC + "�İ��ɶԾ��������˽����!!!!\n" + HIG +
         "   " + wname + HIC + "Ը����" + HIG + lname + HIC + "�İ���" + HIG + master + HIC + "���!!!˫��ͬ�����ս��״̬!!!\n" + HIC +
         "\t���" + HIG + lname + HIC + "Ը����" + HIG + wname + HIC + "��" + CHINESE_D->chinese_number(money) + "������ͽ�!!!\n" NOR, users());

        end_bunch_war(wname, lname, money);

        return 1;
}

public int end_bunch_war(string wname, string lname, int gold)
{
        if (! query(wname + "/member") ||
            ! query(lname + "/member"))
                return 0;

        if (intp(gold) && gold > 0)
        {
                add(wname + "/war_win", 1);
                add(lname + "/war_lose", 1);
                add(wname + "/money", gold);
                add(lname + "/money", -gold);
        }

        set(wname + "/war_kill", 0);
        set(lname + "/war_kill", 0);
        set(wname + "/war_endtime", 0);
        set(lname + "/war_endtime", 0);
        set(wname + "/war_target", "NULL");
        set(lname + "/war_target", "NULL");

        save();
        return 1;
}

// ��������
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

public string query_save_file() { return DATA_DIR "bunchd"; }
