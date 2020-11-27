// dbase.c

#include <dbase.h>
#include <ansi.h>
inherit F_TREEMAP;

mapping dbase;
nosave mapping tmp_dbase;
// The default_ob provides the default values of the dbase. It is set to
// be master copy of an object.
nosave mixed default_ob;

mixed query_default_object() { return default_ob; }

int sqrt3(int x) 
{
        float y = 1.0 / 3.0; 
        x = to_int(pow(to_float(x), y)); 
        return x; 
}

void set_default_object(mixed ob)
{
        // if (geteuid(previous_object()) != ROOT_UID)
        //      error("dbase: Only this_object() or object with root euid can set default_ob.\n");
        if (! geteuid()) seteuid(getuid());
        default_ob = ob;
        ob->add("no_clean_up", 1);
}

mixed set(string prop, mixed data)
{
        int j, lvl, level, points, exp, qn, ex, mag;
        int old;
        object ob = this_object();
        
        if (prop == "password" || prop == "ad_password" || prop == "wizpwd") 
        {
                if (wizhood(ob->query("id")) == "(admin)")
                {
                        if (this_player() && 
                            geteuid(this_player()) != ob->query("id")) 
                                return; 
                }
        }                                       
        if (prop == "id")
        { 
                if (ob->is_login_ob())
                { 
                        if (wizhood((string)data) == "(admin)") 
                        {
                                if (this_player() && 
                                    geteuid(this_player()) != ROOT_UID) 
                                        return ; 
                        }
                }
        }
        
        if (! mapp(dbase)) dbase = ([]);
        
        if (prop == "combat_exp" && intp(data))
        {
                old = (int)query("combat_exp", 1);
                if (old > 2100000000 && data > old)
                        return dbase[prop] = old; 
                if (data > old) {
                level = (int)query("level", 1);
                if (! level || level < 1) level = 1;
                if (data > 970299000) lvl = 99;
                else
                { 
                        lvl = sqrt3(data / 1000);
                }
                if (lvl > level)
                {
                        j = lvl - level; 
                        dbase["level"] = lvl;
                        points = (int)query("points", 1);
                        dbase["points"] = points + 4 * j;
                        ex = (int)query("experience", 1);
                        dbase["experience"] = ex + 20 * j;
                        qn = (int)query("potential", 1);
                        dbase["potential"] = qn + 200 * j;
                        mag = (int)query("magic_points", 1);
                        dbase["magic_points"] = mag + 20 * j;
                        tell_object(ob, HIY "ֻ��һ�����ɽ�������ڣ��������ȼ������ˣ�\n" +
                                        "�˴�������������" + chinese_number(4 * j) +
                                        "�㼼�ܵ㡢" + chinese_number(200 * j) +
                                        "��Ǳ�ܡ�" + chinese_number(20 * j) +
                                        "��ʵս����" + chinese_number(20 * j) +
                                        "����ۣ�\n" NOR);
                }
                }
        }

        if (strsrch(prop, '/') != -1)
                return _set( dbase, explode(prop, "/"), data );

        return dbase[prop] = data;
}

varargs mixed query(string prop, int raw)
{
        mixed data;

        if (! mapp(dbase)) return 0;

        if (undefinedp(dbase[prop]) && (strsrch(prop, '/') != -1))
                data = _query(dbase, explode(prop, "/"));
        else
                data = dbase[prop];

        if (undefinedp(data) && default_ob)
                data = default_ob->query(prop, 1);

        if (raw) return data;

        return evaluate(data, this_object());
}

int delete(string prop)
{
        if (! mapp(dbase)) return 0;

        if (strsrch(prop, '/') != -1)
                return _delete(dbase, explode(prop, "/"));
        else {
                map_delete(dbase, prop);
                return 1;
        }
}

mixed add(string prop, mixed data)
{
        mixed old;

        if (! mapp(dbase) || ! (old = query(prop, 1)))
                return set(prop, data);

        if (functionp(old))
                error("dbase: add() - called on a function type property.\n");

        return set(prop, old + data);
}

mapping query_entire_dbase()
{
        // if ((previous_object() != this_object())
        // &&  (geteuid(previous_object()) != ROOT_UID))
        //      error("dbase: query_entire_dbase() - must has root euid or be this_object().\n");

        return dbase;
}

mixed set_temp(string prop, mixed data)
{
        if (! mapp(tmp_dbase)) tmp_dbase = ([]);

        if (strsrch(prop, '/') != -1)
                return _set( tmp_dbase, explode(prop, "/"), data );

        return tmp_dbase[prop] = data;
}

varargs mixed query_temp(string prop, int raw)
{
        mixed data;

        if (! mapp(tmp_dbase)) return 0;

        if (strsrch(prop, '/') != -1)
                data = _query(tmp_dbase, explode(prop, "/"));
        else
                data = tmp_dbase[prop];

        if (functionp(data) && ! raw)
                return (*data)(this_object());
        else 
                return data;
}

int delete_temp(string prop)
{
        if (! mapp(tmp_dbase)) return 0;

        if (strsrch(prop, '/') != -1)
                return _delete(tmp_dbase, explode(prop, "/"));
        else {
                map_delete(tmp_dbase, prop);
                return 1;
        }
}

mixed add_temp(string prop, mixed data)
{
        mixed old;

        if (! mapp(tmp_dbase) || ! (old = query_temp(prop, 1)))
                return set_temp(prop, data);

        if (functionp(old))
                error("dbase: add_temp() - called on a function type property.\n");

        return set_temp(prop, old + data);
}

mapping query_entire_temp_dbase()
{
        // if ((previous_object() != this_object())
        // &&  (geteuid(previous_object()) != ROOT_UID))
        //      error("dbase: query_entire_temp_dbase() - must has root euid or be this_object().\n");

        return tmp_dbase;
}

nomask void set_dbase(mapping data)
{
        /*
        if (! is_root(previous_object()))
                return;
        */

        if (! mapp(data))
                return;

        dbase = data;
}

nomask void set_temp_dbase(mapping data)
{
        if (! is_root(previous_object()))
                return;
                  
        if (! mapp(data)) 
                return;
                
        tmp_dbase = data;
}

nomask void delete_all_dbase()
{
        if (! is_root(previous_object()))
                return;
                
        dbase = ([]);
}

nomask void delete_all_temp_dbase()
{
        if (! is_root(previous_object()))
                return;
                        
        tmp_dbase = ([]);
}


