// Copyright (C) 2003, by yuchang. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// �������������10��
#define MAX_BUNCH_FAME         1000000000

// ÿ�����������100������
#define MAX_HATRED_PERSON       100

// �����˳�����ʱ��ÿ���Ƴ����ٸ�
#define HATREDP_REMOVED         10

mapping bunch_fame;
mapping last_bunch_fame;

// area's base_name & short
mapping area_fame;

string *bad_weather=({
        "�ܸɺ���Ӱ�죬$N����",
        "���ڱ���Ϯ����$N�ճɵ���",
        "$N�⵽�����ܵ�Ϯ��������",
        "�ٸ����ض�$N����˰��$N����",
        "������$N��Ű����ʧ����",
        "�����Ϯ����$N�������ɾ޴���ʧ",
        "$N������������Ա�������أ���ʧ",
        "$Nͻ��������Ա�������أ����Ѿ޴�",
});

// ���ɶԳ��˳�޶ȵ�����
private int sort_hatred(string id1, string id2, mapping hatred);
public mixed manage_all_area();
public void dismiss_bunch(string fname);

void create()
{
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
        
        // �����������̵㴦��
        manage_all_area();     

        // ������ɵ�������Ϣ
        save();
}

public mixed manage_all_area()
{
        mapping data = ([ ]);
        string *area_npc, *item;        
        string *all_area, *all_bunch;
        string area, bunch, bunch_name, str;
        string *lost;
        string file, bad_area;
        object room, player;
        object npc;
        int weiwang, jizhi, kaifa, zhongcheng, count, i;
        int area_money, bad_money, rest_money, npc_money, cost;
        
        all_area = keys(area_fame) - ({ 0 });   
        
        if (! arrayp(all_area) || sizeof(all_area) < 1)
                return;  

        if (random(sizeof(all_area)) > 10)
        {
                bad_area = area_fame[all_area[random(sizeof(all_area))]];
                room = get_object(bad_area);
                if (! room->query("area/ziyuan"))
                        bad_area = "";   
        }
        else
                bad_area = "";
                        
        foreach (area in all_area)
        {
                reset_eval_cost();
              
                room = get_object(area);
                
                if (! stringp(bunch = room->query("bunch/bunch_name"))) 
                        continue;
                        
                if (! stringp(file = room->query("bunch/npc_file")))
                        continue;
                
                // �̵�ʱ����� NPC ����ʱ����������
                if (! stringp(room->query("bunch/npc_id")) ||
                    ! objectp(npc = present(room->query("bunch/npc_id"), room)))
                        continue;
                
                if (! mapp(query(bunch)))
                {
                        message("channel:rumor", HIM"�����ϵͳ�����ڰ����߽⣬" +
                                room->query("short") + "����������" + "��" + bunch + 
                                "��" + "�Ŀ��ƣ�\n" NOR, users()); 
                                
                        room->delete("bunch");
                        npc->delete("bunch"); 
                        room->save();                                                                                        
                        continue;
                }
                                
                if (room->query("bunch/money") < -1000000 ||
                    query(bunch + "/money") < -100000000)
                {
                        message("channel:rumor", HIM"�����ϵͳ�����ھ�Ӫ���ƣ�" +
                                room->query("short") + "����������" + "��" + bunch + 
                                "��" + "�Ŀ��ƣ�\n" NOR, users());   
                        
                        if (! arrayp(area_npc = query(bunch + "/area")))   
                                area_npc = ({ });
                        else     
                                area_npc -= ({ area, 0 });                                      
                        set(bunch + "/area", area_npc);     
                        
                        if (! arrayp(area_npc = query(bunch + "/npc")))
                                area_npc = ({ });
                        else
                                area_npc -= ({ file, 0 });
                        set(bunch + "/npc", area_npc);
                        
                        // ������������
                        weiwang = bunch_fame[bunch];
                        weiwang -= 1000;
                        if (weiwang < 0) weiwang = 0;
                        bunch_fame[bunch] = weiwang;
                        
                        room->delete("bunch");
                        npc->delete("bunch");
                        room->save();
                        save();
                        continue;
                }         
                        
                zhongcheng = room->query("bunch/zhongcheng");
                if (! intp(zhongcheng) || zhongcheng < 10) 
                        zhongcheng = 10;
                if (zhongcheng > npc->query("bunch/max_zhongcheng"))
                        zhongcheng = npc->query("bunch/max_zhongcheng");         
                zhongcheng -= 1;
                npc->set("bunch/zhongcheng", zhongcheng < 10 ? 10 : zhongcheng);
                room->set("bunch/zhongcheng", zhongcheng < 10 ? 10 : zhongcheng);
                
                if (! room->query("area/ziyuan"))
                {
                        room->save();
                        continue;
                }

                jizhi = room->query("bunch/jizhi");
                kaifa = room->query("bunch/kaifa");
                jizhi += random(2);
                kaifa -= random(2);
                
                area_money = room->query("bunch/money");
                if (! intp(area_money)) area_money = 0;
                if (! intp(jizhi) || jizhi < 6) jizhi = 6;
                if (jizhi > 60) jizhi = 60;
                if (! intp(kaifa) || kaifa < 20) kaifa = 20;
                room->set("bunch/kaifa", kaifa);
                room->set("bunch/jizhi", jizhi);              
                
                if (area_fame[area] == bad_area)   
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
                
                room->set("bunch/money", area_money);
                
                rest_money = area_money - 1000000;  
                if (rest_money < 0) rest_money = 0;
                
                room->add("bunch/money", -rest_money);
                room->set("bunch/last_money", rest_money);                 
                
                room->save();       
                data[bunch] += rest_money;
        }         
        
        all_bunch = keys(bunch_fame);       
        
        if (! arrayp(all_bunch) || sizeof(all_bunch) < 1)
                return;         
                
        lost = ({ });
        foreach (bunch in all_bunch)   
        {
                reset_eval_cost();
                
                npc_money = query(bunch + "/npc_money"); 
                set(bunch + "/last_npc_money", npc_money);
                set(bunch + "/npc_money", 0);  
                
                set(bunch + "/last_area_money", data[bunch]); 
                
                data[bunch] += npc_money; 
                if (data[bunch] < 0) data[bunch] = 0;
                
                data[bunch] /= 2;
                
                if (query(bunch + "/money") < 2000000000)                
                        add(bunch + "/money", data[bunch]);
                        
                cost = 100 * (sizeof(query(bunch + "/npc")) + 
                                sizeof(query(bunch + "/area")) + 
                                sizeof(query(bunch + "/member")));
                          
                add(bunch + "/money", -cost);
                
                data[bunch] /= 2;
                
                add(bunch + "/bangzhu_money", data[bunch]);
                set(bunch + "/last_bangzhu_money", data[bunch]);
                
                if (query(bunch + "/money") < -100000000) 
                {
                        message("channel:rumor", HIW "�����ϵͳ�����ڰ����ʲ��������ؿ��𣬰�ᡸ" + 
                                                 bunch + "���޷�ά���ճ���֧�������߽��ˣ�\n" NOR, users()); 
                        lost += ({ bunch });
                        // bunch = 0;
                        map_delete(data, bunch);
                }
                                
                save();
        }
        
        // all_bunch -= ({ 0 });
        if (arrayp(lost) && sizeof(lost) > 0)
        {
                foreach (bunch_name in lost)
                        dismiss_bunch(bunch_name);
        }
        lost = ({ });

        if (! arrayp(users()) || ! sizeof(users())) return;
                
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
                
                if ((int)player->query("balance") > 2000000000)  
                        tell_object(player, RED "����Ǯׯ��Ǯ�Ѵﵽ��ʮ�����ƽ𣬿�㻨�ɣ�\n" NOR);
                else                
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
}       

public mixed query_area_fame(mixed ob)
{
        string *all_area;

        if (objectp(ob) || stringp(ob))
                return BUNCH_D->query_areas(ob);

        all_area = keys(area_fame) - ({ 0 });   
        
        return all_area;
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


// �鿴�Ƿ���Դ������
public mixed valid_new_bunch(string fname)
{
        if (query(fname + "/member"))
                return "�˼�����н������������ͱ�������ˡ�\n";

        if (! undefinedp(FAMILY_D->query_family_fame(fname))
                || ! undefinedp(LEAGUE_D->query_league_fame(fname)))
                return "�������Ѿ���" + fname + "�ˣ��㻹����ʲô��\n";

        return 0;
}

// ���� U
public void create_bunch(string fname, int base, object *obs)
{
        mapping bunch;
        mapping data;
        string *channels;
        object ob;

        bunch_fame[fname] = base;
        if (! mapp(last_bunch_fame))
                last_bunch_fame = ([ fname : base ]);
        else
                last_bunch_fame[fname] = base;

        data = ([ "member" : obs->query("id"),    
                  "money"  : 100000000,                 
                  "time"   : time() ]);                     

        foreach (ob in obs)
        {
                bunch = ([ "time"  : time(),
                           "bunch_name"  : fname ]);
                if (ob->is_team_leader())
                {
                        data += ([ "bangzhu" : ob->query("id") ]);
                        bunch += ([ "level" : 9 ]);
                        bunch += ([ "title" : "����" ]);
                } else
                {
                        bunch += ([ "level" : 1 ]);
                        bunch += ([ "title" : "����" ]);                        
                } 
                
                ob->set("bunch", bunch);
                        
                channels = ob->query("channels");
                if (! arrayp(channels) || ! sizeof(channels))
                        channels = ({ "party" });
                else
                if (member_array("bunch", channels) == -1)
                        channels += ({ "party" });

                ob->set("channels", channels);
                ob->save();
        }
        
        set(fname, data);
	save();
}

// ��ɢ U
public void dismiss_bunch(string fname)
{
        string *ids;
        string id;
        object ob, npc;

        // ���������Ϣ
        map_delete(bunch_fame, fname);
        if (mapp(last_bunch_fame)) map_delete(last_bunch_fame, fname);

        // ��������е�������ҵ������Ϣ
        ids = query(fname + "/member");

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

        ids = query(fname + "/area");
        
        if (arrayp(ids))
        {
                // �����л��е��̣�������ǵ���Ϣ
                foreach (id in ids)
                {
                        // ������
                        reset_eval_cost();
                        ob = get_object(id);
                        if (! ob) continue;

                        if (stringp(ob->query("bunch/npc_id")) &&
                            objectp(npc = present(ob->query("bunch/npc_id"), ob)))
                                npc->delete("bunch/bunch_name");
                                            
                        ob->delete("bunch");
                        ob->save();                       
                }
        }        
        
        // ������ɵ�������Ϣ
        delete(fname);
}

// ��ѯ�����еĵ��� U
public string *query_members(mixed ob)
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

// ��ѯ�����еĵ��� U
public string *query_areas(mixed ob)
{
        string *area;
        string fname;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(area = query(fname + "/area")))
                return 0;

        return area;
}

// ��ѯ�����еģΣУ� U
public string *query_npcs(mixed ob)
{
        string *npc;
        string fname;

        if (objectp(ob))
                fname = ob->query("bunch/bunch_name");
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(npc = query(fname + "/npc")))
                return 0;

        return npc;
}

// �Ӱ�����ȥ��һ���� U
public varargs void remove_member_from_bunch(mixed fname, string id)
{
        mapping bunch;
        string *member;    
        string *areas;
        string area;
        object room, npc;
        
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

                areas = query(fname + "/area");
        
                if (arrayp(areas))
                {
                        // �����л��е��̣�������ǵ���Ϣ
                        foreach (area in areas)
                        {
                                // ������
                                reset_eval_cost();
                                room = get_object(area);
                                if (! room) continue;

                                if (stringp(room->query("bunch/npc_id")) &&
                                    objectp(npc = present(room->query("bunch/npc_id"), room)))
                                        npc->delete("bunch/bunch_name");
                                            
                                room->delete("bunch");
                                room->save();                       
                        }
                }        
                delete(fname);
        } else
                bunch["member"] = member;
}

// �ڰ���������һ���� U
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

// �ڰ�����ȥ��һ������ U
public void remove_area_into_bunch(string fname, string id, object ob)
{
        mapping bunch;
        string *area;        
        string *npc;
        string file;
        object room;
                
        if (! mapp(bunch = query(fname)) ||
            ! arrayp(area = bunch["area"]))
                // no such bunch or no area in the 
                return 0;              

        area -= ({ id, 0 });
        
        if (sizeof(area) < 1)
                delete(fname + "/area");
        else        
                bunch["area"] = area;                

        room = get_object(id);        
        if (stringp(room->query("bunch/npc_id")) &&
            room->query("bunch/npc_id") == ob->query("id"))
                ob->delete("bunch/bunch_name");
        
        file = base_name(ob);        
        if (room->query("bunch/npc_file") != file)
                file = room->query("bunch/npc_file");
                                        
        if (arrayp(npc = query(fname + "/npc")))
                npc -= ({ file, 0 });        
        bunch[npc] = npc; 

        message("channel:rumor",  HIM "�����ϵͳ��ĳ�ˣ�" + room->short() +
                "���������ᡸ" + fname + "���Ŀ��ƣ�\n" NOR, users());
                        
        room->delete("bunch");
        room->save();
        save();
}

// �ڰ���������һ������ U
public void add_area_into_bunch(string fname, string id, object ob)
{
        mapping bunch;
        string *area;        
        string *npc;
        string file;
        object room;

        if (! arrayp(area = query(fname + "/area")))
                area = ({ });
         
        if (member_array(id, area) != -1)
                return 0;
                
        area += ({ id });
        
        set(fname + "/area", area);
        
        room = get_object(id);
        
        area_fame[id] = room->short(); // �������� file : short

        file = base_name(ob);
 
        bunch = ([ "bunch_name" : fname,
                   "npc_id"     : ob->query("id"),  
                   "npc_name"   : ob->query("name"),
                   "npc_file"   : file,
                   "zhongcheng" : 10,
                   "money"      : 0 ]);
        room->delete("bunch");                
        room->set("bunch", bunch);
        room->save();
        ob->set("bunch/bunch_name", fname);
        ob->set("bunch/zhongcheng", 10);
        ob->set("bunch/max_zhongcheng", 100);

        if (! arrayp(npc = query(fname + "/npc")))
        {       
                npc = ({ file });
        } else
        {
                if (member_array(file, npc) == -1)
                        npc += ({ file });
        } 
                        
        set(fname + "/npc", npc);

        message("channel:rumor", HIM "�����ϵͳ��ĳ�ˣ�" + ob->query("name") +
                "�����ᡸ" + fname + "����\n" NOR, users());
                
        message("channel:rumor", HIM "�����ϵͳ��ĳ�ˣ�" + room->short() +
                "����ᡸ" + fname + "���̲���\n" NOR, users());
                                
        save();
}

// �ڰ����б䶯������������������ʲ��������ȡ�
public void add_info_into_bunch(string fname, string info, mixed n)
{
        if (! mapp(query(fname)))
                return;
                
        if (intp(n))
                add(fname + "/" + info, n);
        else
        if (stringp(n))
                set(fname + "/" + info, n);
}

// �޸İ���ԱȨ��
public void modify_member_auth(string fname, string id, int auth)
{
        mapping member;

        if (! mapp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, keys(member)) == -1)
                return 0;

        member[id][0] = auth;
        set(fname + "/member", member);
	save();
	return;
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

// ��¼�����־�ļ�
public int party_save_record(string fname, string str)
{
	fname = BANG_DIR + fname;
	if(!write_file(fname,str))
		return 0;
	else	return 1;
}

// ������
public void cun_money_to_party(object ob, int amount)
{
	string id, fname;
	mapping party;

	if (! objectp(ob))
		return;

	if (! stringp(fname = ob->query("party/party_name")))
		return;

	id = ob->query("id");
	if (! mapp(party = query(fname)))
                return;

	party["member"][id][2] += amount;
	party["money"] += amount;
	set(fname, party);
	save();
	return;
}

// ��ѯ���������
public int check_party_money(string fname)
{
	return query(fname + "/money");
}

// �Ӱ��ȡ��
public void qu_money_from_party(object ob, int amount)
{
	string id, fname;
	mapping party;

	if (! objectp(ob))
		return;

	if (! stringp(fname = ob->query("party/party_name")))
		return;

	id = ob->query("id");
	if (! mapp(party = query(fname)))
                return;

	party["money"] -= amount;
	set(fname, party);
	save();
	return;
}


public string query_save_file() { return DATA_DIR "bunchd"; }
