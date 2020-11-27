object new(string file_name)
{
        if( !previous_object() ) return 0;

        if( sscanf("filename", "/clone/goods/%*s") ||
            sscanf("filename", "/clone/tessera/%*s") ||
            sscanf("filename", "/clone/tongren/%*s") ||
            sscanf("filename", "/clone/tuteng/%*s") ) {
                if( !is_root(previous_object()) ) {
                        log_file("static/security",
                                 sprintf("%s  %s(%s) want to clone %s.\n",
                                         ctime(time()),
                                         (string)base_filename(previous_object()),
                                         (this_player(1) ? geteuid(this_player(1)) : "???"),
                                         (string)filename));
                        return 0;
                }
        }
        return efun::new(filename);
}

