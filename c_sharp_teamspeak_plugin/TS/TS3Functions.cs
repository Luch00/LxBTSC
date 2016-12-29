
using System;
using System.Runtime.InteropServices;


public partial class NativeConstants
{

    /// TS3_MAX_SIZE_CHANNEL_NAME -> 40
    public const int TS3_MAX_SIZE_CHANNEL_NAME = 40;

    /// TS3_MAX_SIZE_VIRTUALSERVER_NAME -> 64
    public const int TS3_MAX_SIZE_VIRTUALSERVER_NAME = 64;

    /// TS3_MAX_SIZE_CLIENT_NICKNAME -> 64
    public const int TS3_MAX_SIZE_CLIENT_NICKNAME = 64;

    /// TS3_MIN_SIZE_CLIENT_NICKNAME -> 3
    public const int TS3_MIN_SIZE_CLIENT_NICKNAME = 3;

    /// TS3_MAX_SIZE_REASON_MESSAGE -> 80
    public const int TS3_MAX_SIZE_REASON_MESSAGE = 80;

    /// TS3_MAX_SIZE_TEXTMESSAGE -> 1024
    public const int TS3_MAX_SIZE_TEXTMESSAGE = 1024;

    /// TS3_MAX_SIZE_CHANNEL_TOPIC -> 255
    public const int TS3_MAX_SIZE_CHANNEL_TOPIC = 255;

    /// TS3_MAX_SIZE_CHANNEL_DESCRIPTION -> 8192
    public const int TS3_MAX_SIZE_CHANNEL_DESCRIPTION = 8192;

    /// TS3_MAX_SIZE_VIRTUALSERVER_WELCOMEMESSAGE -> 1024
    public const int TS3_MAX_SIZE_VIRTUALSERVER_WELCOMEMESSAGE = 1024;

    /// TS3_MIN_SECONDS_CLIENTID_REUSE -> 300
    public const int TS3_MIN_SECONDS_CLIENTID_REUSE = 300;

    /// SPEAKER_FRONT_LEFT -> 0x1
    public const int SPEAKER_FRONT_LEFT = 1;

    /// SPEAKER_FRONT_RIGHT -> 0x2
    public const int SPEAKER_FRONT_RIGHT = 2;

    /// SPEAKER_FRONT_CENTER -> 0x4
    public const int SPEAKER_FRONT_CENTER = 4;

    /// SPEAKER_LOW_FREQUENCY -> 0x8
    public const int SPEAKER_LOW_FREQUENCY = 8;

    /// SPEAKER_BACK_LEFT -> 0x10
    public const int SPEAKER_BACK_LEFT = 16;

    /// SPEAKER_BACK_RIGHT -> 0x20
    public const int SPEAKER_BACK_RIGHT = 32;

    /// SPEAKER_FRONT_LEFT_OF_CENTER -> 0x40
    public const int SPEAKER_FRONT_LEFT_OF_CENTER = 64;

    /// SPEAKER_FRONT_RIGHT_OF_CENTER -> 0x80
    public const int SPEAKER_FRONT_RIGHT_OF_CENTER = 128;

    /// SPEAKER_BACK_CENTER -> 0x100
    public const int SPEAKER_BACK_CENTER = 256;

    /// SPEAKER_SIDE_LEFT -> 0x200
    public const int SPEAKER_SIDE_LEFT = 512;

    /// SPEAKER_SIDE_RIGHT -> 0x400
    public const int SPEAKER_SIDE_RIGHT = 1024;

    /// SPEAKER_TOP_CENTER -> 0x800
    public const int SPEAKER_TOP_CENTER = 2048;

    /// SPEAKER_TOP_FRONT_LEFT -> 0x1000
    public const int SPEAKER_TOP_FRONT_LEFT = 4096;

    /// SPEAKER_TOP_FRONT_CENTER -> 0x2000
    public const int SPEAKER_TOP_FRONT_CENTER = 8192;

    /// SPEAKER_TOP_FRONT_RIGHT -> 0x4000
    public const int SPEAKER_TOP_FRONT_RIGHT = 16384;

    /// SPEAKER_TOP_BACK_LEFT -> 0x8000
    public const int SPEAKER_TOP_BACK_LEFT = 32768;

    /// SPEAKER_TOP_BACK_CENTER -> 0x10000
    public const int SPEAKER_TOP_BACK_CENTER = 65536;

    /// SPEAKER_TOP_BACK_RIGHT -> 0x20000
    public const int SPEAKER_TOP_BACK_RIGHT = 131072;

    /// SPEAKER_HEADPHONES_LEFT -> 0x10000000
    public const int SPEAKER_HEADPHONES_LEFT = 268435456;

    /// SPEAKER_HEADPHONES_RIGHT -> 0x20000000
    public const int SPEAKER_HEADPHONES_RIGHT = 536870912;

    /// SPEAKER_MONO -> 0x40000000
    public const int SPEAKER_MONO = 1073741824;

    /// PLUGIN_MENU_BUFSZ -> 128
    public const int PLUGIN_MENU_BUFSZ = 128;

    /// PLUGIN_HOTKEY_BUFSZ -> 128
    public const int PLUGIN_HOTKEY_BUFSZ = 128;
}

public enum Visibility
{

    /// ENTER_VISIBILITY -> 0
    ENTER_VISIBILITY = 0,

    RETAIN_VISIBILITY,

    LEAVE_VISIBILITY,
}

public partial class Errors
{
    public const UInt32 ERROR_ok = 0x0000;
    public const UInt32 ERROR_undefined = 0x0001;
    public const UInt32 ERROR_not_implemented = 0x0002;
    public const UInt32 ERROR_ok_no_update = 0x0003;
    public const UInt32 ERROR_dont_notify = 0x0004;
    public const UInt32 ERROR_lib_time_limit_reached = 0x0005;

    //dunno
    public const UInt32 ERROR_command_not_found = 0x0100;
    public const UInt32 ERROR_unable_to_bind_network_port = 0x0101;
    public const UInt32 ERROR_no_network_port_available = 0x0102;

    //client
    public const UInt32 ERROR_client_invalid_id = 0x0200;
    public const UInt32 ERROR_client_nickname_inuse = 0x0201;
    public const UInt32 ERROR_client_protocol_limit_reached = 0x0203;
    public const UInt32 ERROR_client_invalid_type = 0x0204;
    public const UInt32 ERROR_client_already_subscribed = 0x0205;
    public const UInt32 ERROR_client_not_logged_in = 0x0206;
    public const UInt32 ERROR_client_could_not_validate_identity = 0x0207;
    public const UInt32 ERROR_client_version_outdated = 0x020a;
    public const UInt32 ERROR_client_is_flooding = 0x020c;
    public const UInt32 ERROR_client_hacked = 0x020d;
    public const UInt32 ERROR_client_cannot_verify_now = 0x020e;
    public const UInt32 ERROR_client_login_not_permitted = 0x020f;
    public const UInt32 ERROR_client_not_subscribed = 0x0210;

    //channel
    public const UInt32 ERROR_channel_invalid_id = 0x0300;
    public const UInt32 ERROR_channel_protocol_limit_reached = 0x0301;
    public const UInt32 ERROR_channel_already_in = 0x0302;
    public const UInt32 ERROR_channel_name_inuse = 0x0303;
    public const UInt32 ERROR_channel_not_empty = 0x0304;
    public const UInt32 ERROR_channel_can_not_delete_default = 0x0305;
    public const UInt32 ERROR_channel_default_require_permanent = 0x0306;
    public const UInt32 ERROR_channel_invalid_flags = 0x0307;
    public const UInt32 ERROR_channel_parent_not_permanent = 0x0308;
    public const UInt32 ERROR_channel_maxclients_reached = 0x0309;
    public const UInt32 ERROR_channel_maxfamily_reached = 0x030a;
    public const UInt32 ERROR_channel_invalid_order = 0x030b;
    public const UInt32 ERROR_channel_no_filetransfer_supported = 0x030c;
    public const UInt32 ERROR_channel_invalid_password = 0x030d;
    public const UInt32 ERROR_channel_invalid_security_hash = 0x030f; //note 0x030e is defined in public_rare_errors;

    //server
    public const UInt32 ERROR_server_invalid_id = 0x0400;
    public const UInt32 ERROR_server_running = 0x0401;
    public const UInt32 ERROR_server_is_shutting_down = 0x0402;
    public const UInt32 ERROR_server_maxclients_reached = 0x0403;
    public const UInt32 ERROR_server_invalid_password = 0x0404;
    public const UInt32 ERROR_server_is_virtual = 0x0407;
    public const UInt32 ERROR_server_is_not_running = 0x0409;
    public const UInt32 ERROR_server_is_booting = 0x040a;
    public const UInt32 ERROR_server_status_invalid = 0x040b;
    public const UInt32 ERROR_server_version_outdated = 0x040d;
    public const UInt32 ERROR_server_duplicate_running = 0x040e;

    //parameter
    public const UInt32 ERROR_parameter_quote = 0x0600;
    public const UInt32 ERROR_parameter_invalid_count = 0x0601;
    public const UInt32 ERROR_parameter_invalid = 0x0602;
    public const UInt32 ERROR_parameter_not_found = 0x0603;
    public const UInt32 ERROR_parameter_convert = 0x0604;
    public const UInt32 ERROR_parameter_invalid_size = 0x0605;
    public const UInt32 ERROR_parameter_missing = 0x0606;
    public const UInt32 ERROR_parameter_checksum = 0x0607;

    //unsorted, need further investigation
    public const UInt32 ERROR_vs_critical = 0x0700;
    public const UInt32 ERROR_connection_lost = 0x0701;
    public const UInt32 ERROR_not_connected = 0x0702;
    public const UInt32 ERROR_no_cached_connection_info = 0x0703;
    public const UInt32 ERROR_currently_not_possible = 0x0704;
    public const UInt32 ERROR_failed_connection_initialisation = 0x0705;
    public const UInt32 ERROR_could_not_resolve_hostname = 0x0706;
    public const UInt32 ERROR_invalid_server_connection_handler_id = 0x0707;
    public const UInt32 ERROR_could_not_initialise_input_manager = 0x0708;
    public const UInt32 ERROR_clientlibrary_not_initialised = 0x0709;
    public const UInt32 ERROR_serverlibrary_not_initialised = 0x070a;
    public const UInt32 ERROR_whisper_too_many_targets = 0x070b;
    public const UInt32 ERROR_whisper_no_targets = 0x070c;

    //sound
    public const UInt32 ERROR_sound_preprocessor_disabled = 0x0900;
    public const UInt32 ERROR_sound_internal_preprocessor = 0x0901;
    public const UInt32 ERROR_sound_internal_encoder = 0x0902;
    public const UInt32 ERROR_sound_internal_playback = 0x0903;
    public const UInt32 ERROR_sound_no_capture_device_available = 0x0904;
    public const UInt32 ERROR_sound_no_playback_device_available = 0x0905;
    public const UInt32 ERROR_sound_could_not_open_capture_device = 0x0906;
    public const UInt32 ERROR_sound_could_not_open_playback_device = 0x0907;
    public const UInt32 ERROR_sound_handler_has_device = 0x0908;
    public const UInt32 ERROR_sound_invalid_capture_device = 0x0909;
    public const UInt32 ERROR_sound_invalid_playback_device = 0x090a;
    public const UInt32 ERROR_sound_invalid_wave = 0x090b;
    public const UInt32 ERROR_sound_unsupported_wave = 0x090c;
    public const UInt32 ERROR_sound_open_wave = 0x090d;
    public const UInt32 ERROR_sound_internal_capture = 0x090e;
    public const UInt32 ERROR_sound_device_in_use = 0x090f;
    public const UInt32 ERROR_sound_device_already_registerred = 0x0910;
    public const UInt32 ERROR_sound_unknown_device = 0x0911;
    public const UInt32 ERROR_sound_unsupported_frequency = 0x0912;
    public const UInt32 ERROR_sound_invalid_channel_count = 0x0913;
    public const UInt32 ERROR_sound_read_wave = 0x0914;
    public const UInt32 ERROR_sound_need_more_data = 0x0915; //for internal purposes only
    public const UInt32 ERROR_sound_device_busy = 0x0916; //for internal purposes only
    public const UInt32 ERROR_sound_no_data = 0x0917;
    public const UInt32 ERROR_sound_channel_mask_mismatch = 0x0918;


    //permissions
    public const UInt32 ERROR_permissions_client_insufficient = 0x0a08;
    public const UInt32 ERROR_permissions = 0x0a0c;

    //accounting
    public const UInt32 ERROR_accounting_virtualserver_limit_reached = 0x0b00;
    public const UInt32 ERROR_accounting_slot_limit_reached = 0x0b01;
    public const UInt32 ERROR_accounting_license_file_not_found = 0x0b02;
    public const UInt32 ERROR_accounting_license_date_not_ok = 0x0b03;
    public const UInt32 ERROR_accounting_unable_to_connect_to_server = 0x0b04;
    public const UInt32 ERROR_accounting_unknown_error = 0x0b05;
    public const UInt32 ERROR_accounting_server_error = 0x0b06;
    public const UInt32 ERROR_accounting_instance_limit_reached = 0x0b07;
    public const UInt32 ERROR_accounting_instance_check_error = 0x0b08;
    public const UInt32 ERROR_accounting_license_file_invalid = 0x0b09;
    public const UInt32 ERROR_accounting_running_elsewhere = 0x0b0a;
    public const UInt32 ERROR_accounting_instance_duplicated = 0x0b0b;
    public const UInt32 ERROR_accounting_already_started = 0x0b0c;
    public const UInt32 ERROR_accounting_not_started = 0x0b0d;
    public const UInt32 ERROR_accounting_to_many_starts = 0x0b0e;

    //provisioning server
    public const UInt32 ERROR_provisioning_invalid_password = 0x1100;
    public const UInt32 ERROR_provisioning_invalid_request = 0x1101;
    public const UInt32 ERROR_provisioning_no_slots_available = 0x1102;
    public const UInt32 ERROR_provisioning_pool_missing = 0x1103;
    public const UInt32 ERROR_provisioning_pool_unknown = 0x1104;
    public const UInt32 ERROR_provisioning_unknown_ip_location = 0x1105;
    public const UInt32 ERROR_provisioning_internal_tries_exceeded = 0x1106;
    public const UInt32 ERROR_provisioning_too_many_slots_requested = 0x1107;
    public const UInt32 ERROR_provisioning_too_many_reserved = 0x1108;
    public const UInt32 ERROR_provisioning_could_not_connect = 0x1109;
    public const UInt32 ERROR_provisioning_auth_server_not_connected = 0x1110;
    public const UInt32 ERROR_provisioning_auth_data_too_large = 0x1111;
    public const UInt32 ERROR_provisioning_already_initialized = 0x1112;
    public const UInt32 ERROR_provisioning_not_initialized = 0x1113;
    public const UInt32 ERROR_provisioning_connecting = 0x1114;
    public const UInt32 ERROR_provisioning_already_connected = 0x1115;
    public const UInt32 ERROR_provisioning_not_connected = 0x1116;
    public const UInt32 ERROR_provisioning_io_error = 0x1117;
    public const UInt32 ERROR_provisioning_invalid_timeout = 0x1118;
    public const UInt32 ERROR_provisioning_ts3server_not_found = 0x1119;
    public const UInt32 ERROR_provisioning_no_permission = 0x111A;

    public partial class Client
    {
        public const UInt32 ERROR_client_invalid_id = 0x0200;
        public const UInt32 ERROR_client_nickname_inuse = 0x0201;
        public const UInt32 ERROR_client_protocol_limit_reached = 0x0203;
        public const UInt32 ERROR_client_invalid_type = 0x0204;
        public const UInt32 ERROR_client_already_subscribed = 0x0205;
        public const UInt32 ERROR_client_not_logged_in = 0x0206;
        public const UInt32 ERROR_client_could_not_validate_identity = 0x0207;
        public const UInt32 ERROR_client_version_outdated = 0x020a;
        public const UInt32 ERROR_client_is_flooding = 0x020c;
        public const UInt32 ERROR_client_hacked = 0x020d;
        public const UInt32 ERROR_client_cannot_verify_now = 0x020e;
        public const UInt32 ERROR_client_login_not_permitted = 0x020f;
        public const UInt32 ERROR_client_not_subscribed = 0x0210;
    }

    public partial class Channel
    {
        public const UInt32 ERROR_channel_invalid_id = 0x0300;
        public const UInt32 ERROR_channel_protocol_limit_reached = 0x0301;
        public const UInt32 ERROR_channel_already_in = 0x0302;
        public const UInt32 ERROR_channel_name_inuse = 0x0303;
        public const UInt32 ERROR_channel_not_empty = 0x0304;
        public const UInt32 ERROR_channel_can_not_delete_default = 0x0305;
        public const UInt32 ERROR_channel_default_require_permanent = 0x0306;
        public const UInt32 ERROR_channel_invalid_flags = 0x0307;
        public const UInt32 ERROR_channel_parent_not_permanent = 0x0308;
        public const UInt32 ERROR_channel_maxclients_reached = 0x0309;
        public const UInt32 ERROR_channel_maxfamily_reached = 0x030a;
        public const UInt32 ERROR_channel_invalid_order = 0x030b;
        public const UInt32 ERROR_channel_no_filetransfer_supported = 0x030c;
        public const UInt32 ERROR_channel_invalid_password = 0x030d;
        public const UInt32 ERROR_channel_invalid_security_hash = 0x030f; //note 0x030e is defined in public_rare_errors;
    }

    public partial class Server
    {
        public const UInt32 ERROR_server_invalid_id = 0x0400;
        public const UInt32 ERROR_server_running = 0x0401;
        public const UInt32 ERROR_server_is_shutting_down = 0x0402;
        public const UInt32 ERROR_server_maxclients_reached = 0x0403;
        public const UInt32 ERROR_server_invalid_password = 0x0404;
        public const UInt32 ERROR_server_is_virtual = 0x0407;
        public const UInt32 ERROR_server_is_not_running = 0x0409;
        public const UInt32 ERROR_server_is_booting = 0x040a;
        public const UInt32 ERROR_server_status_invalid = 0x040b;
        public const UInt32 ERROR_server_version_outdated = 0x040d;
        public const UInt32 ERROR_server_duplicate_running = 0x040e;
    }

    public partial class Parameter
    {
        public const UInt32 ERROR_parameter_quote = 0x0600;
        public const UInt32 ERROR_parameter_invalid_count = 0x0601;
        public const UInt32 ERROR_parameter_invalid = 0x0602;
        public const UInt32 ERROR_parameter_not_found = 0x0603;
        public const UInt32 ERROR_parameter_convert = 0x0604;
        public const UInt32 ERROR_parameter_invalid_size = 0x0605;
        public const UInt32 ERROR_parameter_missing = 0x0606;
        public const UInt32 ERROR_parameter_checksum = 0x0607;
    }

    public partial class Sound
    {
        public const UInt32 ERROR_sound_preprocessor_disabled = 0x0900;
        public const UInt32 ERROR_sound_internal_preprocessor = 0x0901;
        public const UInt32 ERROR_sound_internal_encoder = 0x0902;
        public const UInt32 ERROR_sound_internal_playback = 0x0903;
        public const UInt32 ERROR_sound_no_capture_device_available = 0x0904;
        public const UInt32 ERROR_sound_no_playback_device_available = 0x0905;
        public const UInt32 ERROR_sound_could_not_open_capture_device = 0x0906;
        public const UInt32 ERROR_sound_could_not_open_playback_device = 0x0907;
        public const UInt32 ERROR_sound_handler_has_device = 0x0908;
        public const UInt32 ERROR_sound_invalid_capture_device = 0x0909;
        public const UInt32 ERROR_sound_invalid_playback_device = 0x090a;
        public const UInt32 ERROR_sound_invalid_wave = 0x090b;
        public const UInt32 ERROR_sound_unsupported_wave = 0x090c;
        public const UInt32 ERROR_sound_open_wave = 0x090d;
        public const UInt32 ERROR_sound_internal_capture = 0x090e;
        public const UInt32 ERROR_sound_device_in_use = 0x090f;
        public const UInt32 ERROR_sound_device_already_registerred = 0x0910;
        public const UInt32 ERROR_sound_unknown_device = 0x0911;
        public const UInt32 ERROR_sound_unsupported_frequency = 0x0912;
        public const UInt32 ERROR_sound_invalid_channel_count = 0x0913;
        public const UInt32 ERROR_sound_read_wave = 0x0914;
        public const UInt32 ERROR_sound_need_more_data = 0x0915; //for internal purposes only
        public const UInt32 ERROR_sound_device_busy = 0x0916; //for internal purposes only
        public const UInt32 ERROR_sound_no_data = 0x0917;
        public const UInt32 ERROR_sound_channel_mask_mismatch = 0x0918;
    }

    public partial class General
    {
        public const UInt32 ERROR_ok = 0x0000;
        public const UInt32 ERROR_undefined = 0x0001;
        public const UInt32 ERROR_not_implemented = 0x0002;
        public const UInt32 ERROR_ok_no_update = 0x0003;
        public const UInt32 ERROR_dont_notify = 0x0004;
        public const UInt32 ERROR_lib_time_limit_reached = 0x0005;

        //dunno
        public const UInt32 ERROR_command_not_found = 0x0100;
        public const UInt32 ERROR_unable_to_bind_network_port = 0x0101;
        public const UInt32 ERROR_no_network_port_available = 0x0102;
    }
    public partial class Permission
    {
        public const UInt32 ERROR_permissions_client_insufficient = 0x0a08;
        public const UInt32 ERROR_permissions = 0x0a0c;
    }

    public partial class Accounting
    {
        public const UInt32 ERROR_accounting_virtualserver_limit_reached = 0x0b00;
        public const UInt32 ERROR_accounting_slot_limit_reached = 0x0b01;
        public const UInt32 ERROR_accounting_license_file_not_found = 0x0b02;
        public const UInt32 ERROR_accounting_license_date_not_ok = 0x0b03;
        public const UInt32 ERROR_accounting_unable_to_connect_to_server = 0x0b04;
        public const UInt32 ERROR_accounting_unknown_error = 0x0b05;
        public const UInt32 ERROR_accounting_server_error = 0x0b06;
        public const UInt32 ERROR_accounting_instance_limit_reached = 0x0b07;
        public const UInt32 ERROR_accounting_instance_check_error = 0x0b08;
        public const UInt32 ERROR_accounting_license_file_invalid = 0x0b09;
        public const UInt32 ERROR_accounting_running_elsewhere = 0x0b0a;
        public const UInt32 ERROR_accounting_instance_duplicated = 0x0b0b;
        public const UInt32 ERROR_accounting_already_started = 0x0b0c;
        public const UInt32 ERROR_accounting_not_started = 0x0b0d;
        public const UInt32 ERROR_accounting_to_many_starts = 0x0b0e;
    }

    public partial class Provisioning
    {
        public const UInt32 ERROR_provisioning_invalid_password = 0x1100;
        public const UInt32 ERROR_provisioning_invalid_request = 0x1101;
        public const UInt32 ERROR_provisioning_no_slots_available = 0x1102;
        public const UInt32 ERROR_provisioning_pool_missing = 0x1103;
        public const UInt32 ERROR_provisioning_pool_unknown = 0x1104;
        public const UInt32 ERROR_provisioning_unknown_ip_location = 0x1105;
        public const UInt32 ERROR_provisioning_internal_tries_exceeded = 0x1106;
        public const UInt32 ERROR_provisioning_too_many_slots_requested = 0x1107;
        public const UInt32 ERROR_provisioning_too_many_reserved = 0x1108;
        public const UInt32 ERROR_provisioning_could_not_connect = 0x1109;
        public const UInt32 ERROR_provisioning_auth_server_not_connected = 0x1110;
        public const UInt32 ERROR_provisioning_auth_data_too_large = 0x1111;
        public const UInt32 ERROR_provisioning_already_initialized = 0x1112;
        public const UInt32 ERROR_provisioning_not_initialized = 0x1113;
        public const UInt32 ERROR_provisioning_connecting = 0x1114;
        public const UInt32 ERROR_provisioning_already_connected = 0x1115;
        public const UInt32 ERROR_provisioning_not_connected = 0x1116;
        public const UInt32 ERROR_provisioning_io_error = 0x1117;
        public const UInt32 ERROR_provisioning_invalid_timeout = 0x1118;
        public const UInt32 ERROR_provisioning_ts3server_not_found = 0x1119;
        public const UInt32 ERROR_provisioning_no_permission = 0x111A;
    }
    public partial class Rare
    {
        //The idea here is: the values are 2 bytes wide, the first byte identifies the group, the second the count within that group

        //client
        public const UInt32 ERROR_client_invalid_password = 0x0208;
        public const UInt32 ERROR_client_too_many_clones_connected = 0x0209;
        public const UInt32 ERROR_client_is_online = 0x020b;

        //channel
        public const UInt32 ERROR_channel_is_private_channel = 0x030e;
        //note 0x030f is defined in public_errors;

        //database
        public const UInt32 ERROR_database = 0x0500;
        public const UInt32 ERROR_database_empty_result = 0x0501;
        public const UInt32 ERROR_database_duplicate_entry = 0x0502;
        public const UInt32 ERROR_database_no_modifications = 0x0503;
        public const UInt32 ERROR_database_constraint = 0x0504;
        public const UInt32 ERROR_database_reinvoke = 0x0505;

        //file transfer
        public const UInt32 ERROR_file_invalid_name = 0x0800;
        public const UInt32 ERROR_file_invalid_permissions = 0x0801;
        public const UInt32 ERROR_file_already_exists = 0x0802;
        public const UInt32 ERROR_file_not_found = 0x0803;
        public const UInt32 ERROR_file_io_error = 0x0804;
        public const UInt32 ERROR_file_invalid_transfer_id = 0x0805;
        public const UInt32 ERROR_file_invalid_path = 0x0806;
        public const UInt32 ERROR_file_no_files_available = 0x0807;
        public const UInt32 ERROR_file_overwrite_excludes_resume = 0x0808;
        public const UInt32 ERROR_file_invalid_size = 0x0809;
        public const UInt32 ERROR_file_already_in_use = 0x080a;
        public const UInt32 ERROR_file_could_not_open_connection = 0x080b;
        public const UInt32 ERROR_file_no_space_left_on_device = 0x080c;
        public const UInt32 ERROR_file_exceeds_file_system_maximum_size = 0x080d;
        public const UInt32 ERROR_file_transfer_connection_timeout = 0x080e;
        public const UInt32 ERROR_file_connection_lost = 0x080f;
        public const UInt32 ERROR_file_exceeds_supplied_size = 0x0810;
        public const UInt32 ERROR_file_transfer_complete = 0x0811;
        public const UInt32 ERROR_file_transfer_canceled = 0x0812;
        public const UInt32 ERROR_file_transfer_interrupted = 0x0813;
        public const UInt32 ERROR_file_transfer_server_quota_exceeded = 0x0814;
        public const UInt32 ERROR_file_transfer_client_quota_exceeded = 0x0815;
        public const UInt32 ERROR_file_transfer_reset = 0x0816;
        public const UInt32 ERROR_file_transfer_limit_reached = 0x0817;

        //permissions
        public const UInt32 ERROR_permission_invalid_group_id = 0x0a00;
        public const UInt32 ERROR_permission_duplicate_entry = 0x0a01;
        public const UInt32 ERROR_permission_invalid_perm_id = 0x0a02;
        public const UInt32 ERROR_permission_empty_result = 0x0a03;
        public const UInt32 ERROR_permission_default_group_forbidden = 0x0a04;
        public const UInt32 ERROR_permission_invalid_size = 0x0a05;
        public const UInt32 ERROR_permission_invalid_value = 0x0a06;
        public const UInt32 ERROR_permissions_group_not_empty = 0x0a07;
        public const UInt32 ERROR_permissions_insufficient_group_power = 0x0a09;
        public const UInt32 ERROR_permissions_insufficient_permission_power = 0x0a0a;
        public const UInt32 ERROR_permission_template_group_is_used = 0x0a0b;
        //0x0a0c is in public_errors.h

        //server
        public const UInt32 ERROR_server_deployment_active = 0x0405;
        public const UInt32 ERROR_server_unable_to_stop_own_server = 0x0406;
        public const UInt32 ERROR_server_wrong_machineid = 0x0408;
        public const UInt32 ERROR_server_modal_quit = 0x040c;

        //messages
        public const UInt32 ERROR_message_invalid_id = 0x0c00;

        //ban
        public const UInt32 ERROR_ban_invalid_id = 0x0d00;
        public const UInt32 ERROR_connect_failed_banned = 0x0d01;
        public const UInt32 ERROR_rename_failed_banned = 0x0d02;
        public const UInt32 ERROR_ban_flooding = 0x0d03;

        //tts
        public const UInt32 ERROR_tts_unable_to_initialize = 0x0e00;

        //privilege key
        public const UInt32 ERROR_privilege_key_invalid = 0x0f00;

        //voip
        public const UInt32 ERROR_voip_pjsua = 0x1000;
        public const UInt32 ERROR_voip_already_initialized = 0x1001;
        public const UInt32 ERROR_voip_too_many_accounts = 0x1002;
        public const UInt32 ERROR_voip_invalid_account = 0x1003;
        public const UInt32 ERROR_voip_internal_error = 0x1004;
        public const UInt32 ERROR_voip_invalid_connectionId = 0x1005;
        public const UInt32 ERROR_voip_cannot_answer_initiated_call = 0x1006;
        public const UInt32 ERROR_voip_not_initialized = 0x1007;

    }
}
public enum ConnectStatus
{

    /// STATUS_DISCONNECTED -> 0
    STATUS_DISCONNECTED = 0,

    STATUS_CONNECTING,

    STATUS_CONNECTED,

    STATUS_CONNECTION_ESTABLISHING,

    STATUS_CONNECTION_ESTABLISHED,
}

public enum TalkStatus
{

    /// STATUS_NOT_TALKING -> 0
    STATUS_NOT_TALKING = 0,

    /// STATUS_TALKING -> 1
    STATUS_TALKING = 1,

    /// STATUS_TALKING_WHILE_DISABLED -> 2
    STATUS_TALKING_WHILE_DISABLED = 2,
}

public enum CodecType
{

    /// CODEC_SPEEX_NARROWBAND -> 0
    CODEC_SPEEX_NARROWBAND = 0,

    CODEC_SPEEX_WIDEBAND,

    CODEC_SPEEX_ULTRAWIDEBAND,

    CODEC_CELT_MONO,

    CODEC_OPUS_VOICE,

    CODEC_OPUS_MUSIC,
}

public enum CodecEncryptionMode
{

    /// CODEC_ENCRYPTION_PER_CHANNEL -> 0
    CODEC_ENCRYPTION_PER_CHANNEL = 0,

    CODEC_ENCRYPTION_FORCED_OFF,

    CODEC_ENCRYPTION_FORCED_ON,
}

public enum TextMessageTargetMode
{

    /// TextMessageTarget_CLIENT -> 1
    TextMessageTarget_CLIENT = 1,

    TextMessageTarget_CHANNEL,

    TextMessageTarget_SERVER,

    TextMessageTarget_MAX,
}

public enum MuteInputStatus
{

    /// MUTEINPUT_NONE -> 0
    MUTEINPUT_NONE = 0,

    MUTEINPUT_MUTED,
}

public enum MuteOutputStatus
{

    /// MUTEOUTPUT_NONE -> 0
    MUTEOUTPUT_NONE = 0,

    MUTEOUTPUT_MUTED,
}

public enum HardwareInputStatus
{

    /// HARDWAREINPUT_DISABLED -> 0
    HARDWAREINPUT_DISABLED = 0,

    HARDWAREINPUT_ENABLED,
}

public enum HardwareOutputStatus
{

    /// HARDWAREOUTPUT_DISABLED -> 0
    HARDWAREOUTPUT_DISABLED = 0,

    HARDWAREOUTPUT_ENABLED,
}

public enum InputDeactivationStatus
{

    /// INPUT_ACTIVE -> 0
    INPUT_ACTIVE = 0,

    /// INPUT_DEACTIVATED -> 1
    INPUT_DEACTIVATED = 1,
}

public enum ReasonIdentifier
{

    /// REASON_NONE -> 0
    REASON_NONE = 0,

    /// REASON_MOVED -> 1
    REASON_MOVED = 1,

    /// REASON_SUBSCRIPTION -> 2
    REASON_SUBSCRIPTION = 2,

    /// REASON_LOST_CONNECTION -> 3
    REASON_LOST_CONNECTION = 3,

    /// REASON_KICK_CHANNEL -> 4
    REASON_KICK_CHANNEL = 4,

    /// REASON_KICK_SERVER -> 5
    REASON_KICK_SERVER = 5,

    /// REASON_KICK_SERVER_BAN -> 6
    REASON_KICK_SERVER_BAN = 6,

    /// REASON_SERVERSTOP -> 7
    REASON_SERVERSTOP = 7,

    /// REASON_CLIENTDISCONNECT -> 8
    REASON_CLIENTDISCONNECT = 8,

    /// REASON_CHANNELUPDATE -> 9
    REASON_CHANNELUPDATE = 9,

    /// REASON_CHANNELEDIT -> 10
    REASON_CHANNELEDIT = 10,

    /// REASON_CLIENTDISCONNECT_SERVER_SHUTDOWN -> 11
    REASON_CLIENTDISCONNECT_SERVER_SHUTDOWN = 11,
}

public enum ChannelProperties
{

    /// CHANNEL_NAME -> 0
    CHANNEL_NAME = 0,

    CHANNEL_TOPIC,

    CHANNEL_DESCRIPTION,

    CHANNEL_PASSWORD,

    CHANNEL_CODEC,

    CHANNEL_CODEC_QUALITY,

    CHANNEL_MAXCLIENTS,

    CHANNEL_MAXFAMILYCLIENTS,

    CHANNEL_ORDER,

    CHANNEL_FLAG_PERMANENT,

    CHANNEL_FLAG_SEMI_PERMANENT,

    CHANNEL_FLAG_DEFAULT,

    CHANNEL_FLAG_PASSWORD,

    CHANNEL_CODEC_LATENCY_FACTOR,

    CHANNEL_CODEC_IS_UNENCRYPTED,

    CHANNEL_ENDMARKER,
}

public enum ClientProperties
{

    /// CLIENT_UNIQUE_IDENTIFIER -> 0
    CLIENT_UNIQUE_IDENTIFIER = 0,

    CLIENT_NICKNAME,

    CLIENT_VERSION,

    CLIENT_PLATFORM,

    CLIENT_FLAG_TALKING,

    CLIENT_INPUT_MUTED,

    CLIENT_OUTPUT_MUTED,

    CLIENT_OUTPUTONLY_MUTED,

    CLIENT_INPUT_HARDWARE,

    CLIENT_OUTPUT_HARDWARE,

    CLIENT_INPUT_DEACTIVATED,

    CLIENT_IDLE_TIME,

    CLIENT_DEFAULT_CHANNEL,

    CLIENT_DEFAULT_CHANNEL_PASSWORD,

    CLIENT_SERVER_PASSWORD,

    CLIENT_META_DATA,

    CLIENT_IS_MUTED,

    CLIENT_IS_RECORDING,

    CLIENT_VOLUME_MODIFICATOR,

    CLIENT_VERSION_SIGN,

    CLIENT_ENDMARKER,
}

public enum VirtualServerProperties
{

    /// VIRTUALSERVER_UNIQUE_IDENTIFIER -> 0
    VIRTUALSERVER_UNIQUE_IDENTIFIER = 0,

    VIRTUALSERVER_NAME,

    VIRTUALSERVER_WELCOMEMESSAGE,

    VIRTUALSERVER_PLATFORM,

    VIRTUALSERVER_VERSION,

    VIRTUALSERVER_MAXCLIENTS,

    VIRTUALSERVER_PASSWORD,

    VIRTUALSERVER_CLIENTS_ONLINE,

    VIRTUALSERVER_CHANNELS_ONLINE,

    VIRTUALSERVER_CREATED,

    VIRTUALSERVER_UPTIME,

    VIRTUALSERVER_CODEC_ENCRYPTION_MODE,

    VIRTUALSERVER_ENDMARKER,
}

public enum ConnectionProperties
{

    /// CONNECTION_PING -> 0
    CONNECTION_PING = 0,

    CONNECTION_PING_DEVIATION,

    CONNECTION_CONNECTED_TIME,

    CONNECTION_IDLE_TIME,

    CONNECTION_CLIENT_IP,

    CONNECTION_CLIENT_PORT,

    CONNECTION_SERVER_IP,

    CONNECTION_SERVER_PORT,

    CONNECTION_PACKETS_SENT_SPEECH,

    CONNECTION_PACKETS_SENT_KEEPALIVE,

    CONNECTION_PACKETS_SENT_CONTROL,

    CONNECTION_PACKETS_SENT_TOTAL,

    CONNECTION_BYTES_SENT_SPEECH,

    CONNECTION_BYTES_SENT_KEEPALIVE,

    CONNECTION_BYTES_SENT_CONTROL,

    CONNECTION_BYTES_SENT_TOTAL,

    CONNECTION_PACKETS_RECEIVED_SPEECH,

    CONNECTION_PACKETS_RECEIVED_KEEPALIVE,

    CONNECTION_PACKETS_RECEIVED_CONTROL,

    CONNECTION_PACKETS_RECEIVED_TOTAL,

    CONNECTION_BYTES_RECEIVED_SPEECH,

    CONNECTION_BYTES_RECEIVED_KEEPALIVE,

    CONNECTION_BYTES_RECEIVED_CONTROL,

    CONNECTION_BYTES_RECEIVED_TOTAL,

    CONNECTION_PACKETLOSS_SPEECH,

    CONNECTION_PACKETLOSS_KEEPALIVE,

    CONNECTION_PACKETLOSS_CONTROL,

    CONNECTION_PACKETLOSS_TOTAL,

    CONNECTION_SERVER2CLIENT_PACKETLOSS_SPEECH,

    CONNECTION_SERVER2CLIENT_PACKETLOSS_KEEPALIVE,

    CONNECTION_SERVER2CLIENT_PACKETLOSS_CONTROL,

    CONNECTION_SERVER2CLIENT_PACKETLOSS_TOTAL,

    CONNECTION_CLIENT2SERVER_PACKETLOSS_SPEECH,

    CONNECTION_CLIENT2SERVER_PACKETLOSS_KEEPALIVE,

    CONNECTION_CLIENT2SERVER_PACKETLOSS_CONTROL,

    CONNECTION_CLIENT2SERVER_PACKETLOSS_TOTAL,

    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_SPEECH,

    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_KEEPALIVE,

    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_CONTROL,

    CONNECTION_BANDWIDTH_SENT_LAST_SECOND_TOTAL,

    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_SPEECH,

    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_KEEPALIVE,

    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_CONTROL,

    CONNECTION_BANDWIDTH_SENT_LAST_MINUTE_TOTAL,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_SPEECH,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_KEEPALIVE,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_CONTROL,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_SECOND_TOTAL,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_SPEECH,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_KEEPALIVE,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_CONTROL,

    CONNECTION_BANDWIDTH_RECEIVED_LAST_MINUTE_TOTAL,

    CONNECTION_ENDMARKER,
}

public enum LogTypes
{

    /// LogType_NONE -> 0x0000
    LogType_NONE = 0,

    /// LogType_FILE -> 0x0001
    LogType_FILE = 1,

    /// LogType_CONSOLE -> 0x0002
    LogType_CONSOLE = 2,

    /// LogType_USERLOGGING -> 0x0004
    LogType_USERLOGGING = 4,

    /// LogType_NO_NETLOGGING -> 0x0008
    LogType_NO_NETLOGGING = 8,

    /// LogType_DATABASE -> 0x0010
    LogType_DATABASE = 16,
}

public enum LogLevel
{

    /// LogLevel_CRITICAL -> 0
    LogLevel_CRITICAL = 0,

    LogLevel_ERROR,

    LogLevel_WARNING,

    LogLevel_DEBUG,

    LogLevel_INFO,

    LogLevel_DEVEL,
}

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
public struct TS3_VECTOR
{

    /// float
    public float x;

    /// float
    public float y;

    /// float
    public float z;
}

public struct anyID
{
    public ushort value;

    public anyID(ushort v)
    {
        value = v;
    }
}

public enum GroupWhisperType
{

    /// GROUPWHISPERTYPE_SERVERGROUP -> 0
    GROUPWHISPERTYPE_SERVERGROUP = 0,

    /// GROUPWHISPERTYPE_CHANNELGROUP -> 1
    GROUPWHISPERTYPE_CHANNELGROUP = 1,

    /// GROUPWHISPERTYPE_CHANNELCOMMANDER -> 2
    GROUPWHISPERTYPE_CHANNELCOMMANDER = 2,

    /// GROUPWHISPERTYPE_ALLCLIENTS -> 3
    GROUPWHISPERTYPE_ALLCLIENTS = 3,

    GROUPWHISPERTYPE_ENDMARKER,
}

public enum GroupWhisperTargetMode
{

    /// GROUPWHISPERTARGETMODE_ALL -> 0
    GROUPWHISPERTARGETMODE_ALL = 0,

    /// GROUPWHISPERTARGETMODE_CURRENTCHANNEL -> 1
    GROUPWHISPERTARGETMODE_CURRENTCHANNEL = 1,

    /// GROUPWHISPERTARGETMODE_PARENTCHANNEL -> 2
    GROUPWHISPERTARGETMODE_PARENTCHANNEL = 2,

    /// GROUPWHISPERTARGETMODE_ALLPARENTCHANNELS -> 3
    GROUPWHISPERTARGETMODE_ALLPARENTCHANNELS = 3,

    /// GROUPWHISPERTARGETMODE_CHANNELFAMILY -> 4
    GROUPWHISPERTARGETMODE_CHANNELFAMILY = 4,

    /// GROUPWHISPERTARGETMODE_ANCESTORCHANNELFAMILY -> 5
    GROUPWHISPERTARGETMODE_ANCESTORCHANNELFAMILY = 5,

    /// GROUPWHISPERTARGETMODE_SUBCHANNELS -> 6
    GROUPWHISPERTARGETMODE_SUBCHANNELS = 6,

    GROUPWHISPERTARGETMODE_ENDMARKER,
}

public enum MonoSoundDestination
{

    /// MONO_SOUND_DESTINATION_ALL -> 0
    MONO_SOUND_DESTINATION_ALL = 0,

    /// MONO_SOUND_DESTINATION_FRONT_CENTER -> 1
    MONO_SOUND_DESTINATION_FRONT_CENTER = 1,

    /// MONO_SOUND_DESTINATION_FRONT_LEFT_AND_RIGHT -> 2
    MONO_SOUND_DESTINATION_FRONT_LEFT_AND_RIGHT = 2,
}

public enum PluginConfigureOffer
{

    /// PLUGIN_OFFERS_NO_CONFIGURE -> 0
    PLUGIN_OFFERS_NO_CONFIGURE = 0,

    PLUGIN_OFFERS_CONFIGURE_NEW_THREAD,

    PLUGIN_OFFERS_CONFIGURE_QT_THREAD,
}

public enum PluginMessageTarget
{

    /// PLUGIN_MESSAGE_TARGET_SERVER -> 0
    PLUGIN_MESSAGE_TARGET_SERVER = 0,

    PLUGIN_MESSAGE_TARGET_CHANNEL,
}

public enum PluginItemType
{

    /// PLUGIN_SERVER -> 0
    PLUGIN_SERVER = 0,

    PLUGIN_CHANNEL,

    PLUGIN_CLIENT,
}

public enum PluginMenuType : int
{

    /// PLUGIN_MENU_TYPE_GLOBAL -> 0
    PLUGIN_MENU_TYPE_GLOBAL = 0,

    PLUGIN_MENU_TYPE_CHANNEL,

    PLUGIN_MENU_TYPE_CLIENT,
}

public enum MenuType : int {
    MENU_ID_CLIENT_1 = 1,
    MENU_ID_CLIENT_2 = 2,
    MENU_ID_CHANNEL_1 = 3,
    MENU_ID_CHANNEL_2 = 4,
    MENU_ID_CHANNEL_3 = 5,
    MENU_ID_GLOBAL_1 = 6,
    MENU_ID_GLOBAL_2 = 7
};

[StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)] // 
public struct MiniClientExport
{
    private anyID id;

    public UInt64 channel;

    [MarshalAsAttribute(UnmanagedType.LPStr)]
    public string indent;

    [MarshalAsAttribute(UnmanagedType.LPStr)]
    public string nickname;
}

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential, CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
public unsafe struct PluginMenuItem
{

    /// PluginMenuType
    public PluginMenuType type;

    /// int
    public int id;

    // [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 128)]
    public fixed char text[128];

    public fixed char icon[128];
    /// char[128]
    // [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 128)]
    // public string text;

    /// char[128]
    //[System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 128)]
    //public string icon;
}

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential, CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
public struct PluginHotkey
{

    /// char[128]
    [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 128)]
    public string keyword;

    /// char[128]
    [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 128)]
    public string description;
}

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Explicit)]
public struct Anonymous_344b905a_b983_4217_a33a_e37f6170018f
{

    /// char*
    [System.Runtime.InteropServices.FieldOffsetAttribute(0)]
    public System.IntPtr uuid;

    /// PluginBookmarkList*
    [System.Runtime.InteropServices.FieldOffsetAttribute(0)]
    public System.IntPtr folder;
}

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential, CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
public struct PluginBookmarkItem
{

    /// char*
    [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)]
    public string name;

    /// unsigned char
    public byte isFolder;

    /// unsigned char[3]
    [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = 3)]
    public string reserved;

    /// Anonymous_344b905a_b983_4217_a33a_e37f6170018f
    public Anonymous_344b905a_b983_4217_a33a_e37f6170018f Union1;
}

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
public struct PluginBookmarkList
{

    /// int
    public int itemcount;

    /// PluginBookmarkItem[1]
    [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = 1, ArraySubType = System.Runtime.InteropServices.UnmanagedType.Struct)]
    public PluginBookmarkItem[] items;
}

public enum PluginGuiProfile
{

    /// PLUGIN_GUI_SOUND_CAPTURE -> 0
    PLUGIN_GUI_SOUND_CAPTURE = 0,

    PLUGIN_GUI_SOUND_PLAYBACK,

    PLUGIN_GUI_HOTKEY,

    PLUGIN_GUI_SOUNDPACK,

    PLUGIN_GUI_IDENTITY,
}

public enum PluginConnectTab
{

    /// PLUGIN_CONNECT_TAB_NEW -> 0
    PLUGIN_CONNECT_TAB_NEW = 0,

    PLUGIN_CONNECT_TAB_CURRENT,

    PLUGIN_CONNECT_TAB_NEW_IF_CURRENT_CONNECTED,
}

/// Return Type: unsigned int
///result: char**
public delegate uint TS3Functions_getClientLibVersion(ref System.IntPtr result);

/// Return Type: unsigned int
///result: uint64*
public delegate uint TS3Functions_getClientLibVersionNumber(ref ulong result);

/// Return Type: unsigned int
///port: int
///result: uint64*
public delegate uint TS3Functions_spawnNewServerConnectionHandler(int port, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_destroyServerConnectionHandler(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///errorCode: unsigned int
///error: char**
public delegate uint TS3Functions_getErrorMessage(uint errorCode, ref System.IntPtr error);

/// Return Type: unsigned int
///pointer: void*
public delegate uint TS3Functions_freeMemory(System.IntPtr pointer);

/// Return Type: unsigned int
///logMessage: char*
///severity: LogLevel
///channel: char*
///logID: uint64->unsigned __int64
public delegate uint TS3Functions_logMessage([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string logMessage, LogLevel severity, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channel, ulong logID);

/// Return Type: unsigned int
///modeID: char*
///result: char****
public delegate uint TS3Functions_getPlaybackDeviceList([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string modeID, ref System.IntPtr result);

/// Return Type: unsigned int
///result: char***
public delegate uint TS3Functions_getPlaybackModeList(ref System.IntPtr result);

/// Return Type: unsigned int
///modeID: char*
///result: char****
public delegate uint TS3Functions_getCaptureDeviceList([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string modeID, ref System.IntPtr result);

/// Return Type: unsigned int
///result: char***
public delegate uint TS3Functions_getCaptureModeList(ref System.IntPtr result);

/// Return Type: unsigned int
///modeID: char*
///result: char***
public delegate uint TS3Functions_getDefaultPlaybackDevice([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string modeID, ref System.IntPtr result);

/// Return Type: unsigned int
///result: char**
public delegate uint TS3Functions_getDefaultPlayBackMode(ref System.IntPtr result);

/// Return Type: unsigned int
///modeID: char*
///result: char***
public delegate uint TS3Functions_getDefaultCaptureDevice([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string modeID, ref System.IntPtr result);

/// Return Type: unsigned int
///result: char**
public delegate uint TS3Functions_getDefaultCaptureMode(ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///modeID: char*
///playbackDevice: char*
public delegate uint TS3Functions_openPlaybackDevice(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string modeID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string playbackDevice);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///modeID: char*
///captureDevice: char*
public delegate uint TS3Functions_openCaptureDevice(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string modeID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string captureDevice);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: char**
///isDefault: int*
public delegate uint TS3Functions_getCurrentPlaybackDeviceName(ulong serverConnectionHandlerID, ref System.IntPtr result, ref int isDefault);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: char**
public delegate uint TS3Functions_getCurrentPlayBackMode(ulong serverConnectionHandlerID, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: char**
///isDefault: int*
public delegate uint TS3Functions_getCurrentCaptureDeviceName(ulong serverConnectionHandlerID, ref System.IntPtr result, ref int isDefault);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: char**
public delegate uint TS3Functions_getCurrentCaptureMode(ulong serverConnectionHandlerID, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_initiateGracefulPlaybackShutdown(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_closePlaybackDevice(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_closeCaptureDevice(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_activateCaptureDevice(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///path: char*
///loop: int
///waveHandle: uint64*
public delegate uint TS3Functions_playWaveFileHandle(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string path, int loop, ref ulong waveHandle);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///waveHandle: uint64->unsigned __int64
///pause: int
public delegate uint TS3Functions_pauseWaveFileHandle(ulong serverConnectionHandlerID, ulong waveHandle, int pause);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///waveHandle: uint64->unsigned __int64
public delegate uint TS3Functions_closeWaveFileHandle(ulong serverConnectionHandlerID, ulong waveHandle);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///path: char*
public delegate uint TS3Functions_playWaveFile(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string path);

/// Return Type: unsigned int
///deviceID: char*
///deviceDisplayName: char*
///capFrequency: int
///capChannels: int
///playFrequency: int
///playChannels: int
public delegate uint TS3Functions_registerCustomDevice([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string deviceID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string deviceDisplayName, int capFrequency, int capChannels, int playFrequency, int playChannels);

/// Return Type: unsigned int
///deviceID: char*
public delegate uint TS3Functions_unregisterCustomDevice([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string deviceID);

/// Return Type: unsigned int
///deviceName: char*
///buffer: short*
///samples: int
public delegate uint TS3Functions_processCustomCaptureData([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string deviceName, ref short buffer, int samples);

/// Return Type: unsigned int
///deviceName: char*
///buffer: short*
///samples: int
public delegate uint TS3Functions_acquireCustomPlaybackData([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string deviceName, ref short buffer, int samples);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ident: char*
///result: float*
public delegate uint TS3Functions_getPreProcessorInfoValueFloat(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ident, ref float result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ident: char*
///result: char**
public delegate uint TS3Functions_getPreProcessorConfigValue(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ident, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ident: char*
///value: char*
public delegate uint TS3Functions_setPreProcessorConfigValue(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ident, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ident: char*
///result: char**
public delegate uint TS3Functions_getEncodeConfigValue(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ident, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ident: char*
///result: float*
public delegate uint TS3Functions_getPlaybackConfigValueAsFloat(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ident, ref float result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ident: char*
///value: char*
public delegate uint TS3Functions_setPlaybackConfigValue(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ident, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///value: float
public delegate uint TS3Functions_setClientVolumeModifier(ulong serverConnectionHandlerID, ushort clientID, float value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_startVoiceRecording(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_stopVoiceRecording(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///position: TS3_VECTOR*
///forward: TS3_VECTOR*
///up: TS3_VECTOR*
public delegate uint TS3Functions_systemset3DListenerAttributes(ulong serverConnectionHandlerID, ref TS3_VECTOR position, ref TS3_VECTOR forward, ref TS3_VECTOR up);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///waveHandle: uint64->unsigned __int64
///position: TS3_VECTOR*
public delegate uint TS3Functions_set3DWaveAttributes(ulong serverConnectionHandlerID, ulong waveHandle, ref TS3_VECTOR position);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///distanceFactor: float
///rolloffScale: float
public delegate uint TS3Functions_systemset3DSettings(ulong serverConnectionHandlerID, float distanceFactor, float rolloffScale);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///position: TS3_VECTOR*
public delegate uint TS3Functions_channelset3DAttributes(ulong serverConnectionHandlerID, ushort clientID, ref TS3_VECTOR position);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///identity: char*
///ip: char*
///port: unsigned int
///nickname: char*
///defaultChannelArray: char**
///defaultChannelPassword: char*
///serverPassword: char*
public delegate uint TS3Functions_startConnection(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string identity, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ip, uint port, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string nickname, ref System.IntPtr defaultChannelArray, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string defaultChannelPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverPassword);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///quitMessage: char*
public delegate uint TS3Functions_stopConnection(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string quitMessage);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///newChannelID: uint64->unsigned __int64
///password: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientMove(ulong serverConnectionHandlerID, ushort clientID, ulong newChannelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string password, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///returnCode: char*
public delegate uint TS3Functions_requestClientVariables(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///kickReason: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientKickFromChannel(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string kickReason, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///kickReason: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientKickFromServer(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string kickReason, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///force: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelDelete(ulong serverConnectionHandlerID, ulong channelID, int force, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///newChannelParentID: uint64->unsigned __int64
///newChannelOrder: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelMove(ulong serverConnectionHandlerID, ulong channelID, ulong newChannelParentID, ulong newChannelOrder, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///message: char*
///targetClientID: anyID->unsigned short
///returnCode: char*
//public delegate uint TS3Functions_requestSendPrivateTextMsg(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message, ushort targetClientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);
public delegate uint TS3Functions_requestSendPrivateTextMsg(ulong serverConnectionHandlerID, IntPtr message, ushort targetClientID, [In()] [MarshalAs(UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///message: char*
///targetChannelID: uint64->unsigned __int64
///returnCode: char*
//public delegate uint TS3Functions_requestSendChannelTextMsg(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message, ulong targetChannelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);
public delegate uint TS3Functions_requestSendChannelTextMsg(ulong serverConnectionHandlerID, IntPtr message, ulong targetChannelID, [In()] [MarshalAs(UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///message: char*
///returnCode: char*
//public delegate uint TS3Functions_requestSendServerTextMsg(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);
public delegate uint TS3Functions_requestSendServerTextMsg(ulong serverConnectionHandlerID, IntPtr message, [In()] [MarshalAs(UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///returnCode: char*
public delegate uint TS3Functions_requestConnectionInfo(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///targetChannelIDArray: uint64*
///targetClientIDArray: anyID*
///returnCode: char*
public delegate uint TS3Functions_requestClientSetWhisperList(ulong serverConnectionHandlerID, ushort clientID, ref ulong targetChannelIDArray, ref ushort targetClientIDArray, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelIDArray: uint64*
///returnCode: char*
public delegate uint TS3Functions_requestChannelSubscribe(ulong serverConnectionHandlerID, ref ulong channelIDArray, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelSubscribeAll(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelIDArray: uint64*
///returnCode: char*
public delegate uint TS3Functions_requestChannelUnsubscribe(ulong serverConnectionHandlerID, ref ulong channelIDArray, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelUnsubscribeAll(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelDescription(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientIDArray: anyID*
///returnCode: char*
public delegate uint TS3Functions_requestMuteClients(ulong serverConnectionHandlerID, ref ushort clientIDArray, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientIDArray: anyID*
///returnCode: char*
public delegate uint TS3Functions_requestUnmuteClients(ulong serverConnectionHandlerID, ref ushort clientIDArray, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///message: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientPoke(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientUniqueIdentifier: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientIDs(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string clientUniqueIdentifier, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientUniqueIdentifier: char*
///clientID: anyID->unsigned short
///returnCode: char*
public delegate uint TS3Functions_clientChatClosed(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string clientUniqueIdentifier, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///returnCode: char*
public delegate uint TS3Functions_clientChatComposing(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///password: char*
///description: char*
///duration: uint64->unsigned __int64
///targetChannelID: uint64->unsigned __int64
///targetChannelPW: char*
///returnCode: char*
public delegate uint TS3Functions_requestServerTemporaryPasswordAdd(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string password, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string description, ulong duration, ulong targetChannelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string targetChannelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///password: char*
///returnCode: char*
public delegate uint TS3Functions_requestServerTemporaryPasswordDel(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string password, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestServerTemporaryPasswordList(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: anyID*
public delegate uint TS3Functions_getClientID(ulong serverConnectionHandlerID, ref ushort result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: int*
public delegate uint TS3Functions_getClientSelfVariableAsInt(ulong serverConnectionHandlerID, System.IntPtr flag, ref int result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: char**
public delegate uint TS3Functions_getClientSelfVariableAsString(ulong serverConnectionHandlerID, System.IntPtr flag, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///value: int
public delegate uint TS3Functions_setClientSelfVariableAsInt(ulong serverConnectionHandlerID, System.IntPtr flag, int value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///value: char*
public delegate uint TS3Functions_setClientSelfVariableAsString(ulong serverConnectionHandlerID, System.IntPtr flag, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_flushClientSelfUpdates(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///flag: size_t->unsigned int
///result: int*
public delegate uint TS3Functions_getClientVariableAsInt(ulong serverConnectionHandlerID, ushort clientID, System.IntPtr flag, ref int result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///flag: size_t->unsigned int
///result: uint64*
public delegate uint TS3Functions_getClientVariableAsUInt64(ulong serverConnectionHandlerID, ushort clientID, System.IntPtr flag, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///flag: size_t->unsigned int
///result: char**
public delegate uint TS3Functions_getClientVariableAsString(ulong serverConnectionHandlerID, ushort clientID, System.IntPtr flag, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: anyID**
public delegate uint TS3Functions_getClientList(ulong serverConnectionHandlerID, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///result: uint64*
public delegate uint TS3Functions_getChannelOfClient(ulong serverConnectionHandlerID, ushort clientID, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: int*
public delegate uint TS3Functions_getChannelVariableAsInt(ulong serverConnectionHandlerID, ulong channelID, System.IntPtr flag, ref int result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: uint64*
public delegate uint TS3Functions_getChannelVariableAsUInt64(ulong serverConnectionHandlerID, ulong channelID, System.IntPtr flag, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: char**
public delegate uint TS3Functions_getChannelVariableAsString(ulong serverConnectionHandlerID, ulong channelID, System.IntPtr flag, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelNameArray: char**
///result: uint64*
public delegate uint TS3Functions_getChannelIDFromChannelNames(ulong serverConnectionHandlerID, ref System.IntPtr channelNameArray, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///flag: size_t->unsigned int
///value: int
public delegate uint TS3Functions_setChannelVariableAsInt(ulong serverConnectionHandlerID, ulong channelID, System.IntPtr flag, int value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///flag: size_t->unsigned int
///value: uint64->unsigned __int64
public delegate uint TS3Functions_setChannelVariableAsUInt64(ulong serverConnectionHandlerID, ulong channelID, System.IntPtr flag, ulong value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///flag: size_t->unsigned int
///value: char*
public delegate uint TS3Functions_setChannelVariableAsString(ulong serverConnectionHandlerID, ulong channelID, System.IntPtr flag, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string value);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_flushChannelUpdates(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelParentID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_flushChannelCreation(ulong serverConnectionHandlerID, ulong channelParentID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: uint64**
public delegate uint TS3Functions_getChannelList(ulong serverConnectionHandlerID, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///result: anyID**
public delegate uint TS3Functions_getChannelClientList(ulong serverConnectionHandlerID, ulong channelID, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///result: uint64*
public delegate uint TS3Functions_getParentChannelOfChannel(ulong serverConnectionHandlerID, ulong channelID, ref ulong result);

/// Return Type: unsigned int
///result: uint64**
public delegate uint TS3Functions_getServerConnectionHandlerList(ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: int*
public delegate uint TS3Functions_getServerVariableAsInt(ulong serverConnectionHandlerID, System.IntPtr flag, ref int result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: uint64*
public delegate uint TS3Functions_getServerVariableAsUInt64(ulong serverConnectionHandlerID, System.IntPtr flag, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///flag: size_t->unsigned int
///result: char**
public delegate uint TS3Functions_getServerVariableAsString(ulong serverConnectionHandlerID, System.IntPtr flag, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
public delegate uint TS3Functions_requestServerVariables(ulong serverConnectionHandlerID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///result: int*
public delegate uint TS3Functions_getConnectionStatus(ulong serverConnectionHandlerID, ref int result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///flag: size_t->unsigned int
///result: uint64*
public delegate uint TS3Functions_getConnectionVariableAsUInt64(ulong serverConnectionHandlerID, ushort clientID, System.IntPtr flag, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///flag: size_t->unsigned int
///result: double*
public delegate uint TS3Functions_getConnectionVariableAsDouble(ulong serverConnectionHandlerID, ushort clientID, System.IntPtr flag, ref double result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///flag: size_t->unsigned int
///result: char**
public delegate uint TS3Functions_getConnectionVariableAsString(ulong serverConnectionHandlerID, ushort clientID, System.IntPtr flag, ref System.IntPtr result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
public delegate uint TS3Functions_cleanUpConnectionInfo(ulong serverConnectionHandlerID, ushort clientID);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientUniqueIdentifier: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientDBIDfromUID(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string clientUniqueIdentifier, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientUniqueIdentifier: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientNamefromUID(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string clientUniqueIdentifier, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestClientNamefromDBID(ulong serverConnectionHandlerID, ulong clientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///clientDescription: char*
///returnCode: char*
public delegate uint TS3Functions_requestClientEditDescription(ulong serverConnectionHandlerID, ushort clientID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string clientDescription, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///isTalker: int
///returnCode: char*
public delegate uint TS3Functions_requestClientSetIsTalker(ulong serverConnectionHandlerID, ushort clientID, int isTalker, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///isTalkerRequest: int
///isTalkerRequestMessage: char*
///returnCode: char*
public delegate uint TS3Functions_requestIsTalker(ulong serverConnectionHandlerID, int isTalkerRequest, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string isTalkerRequestMessage, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///command: char*
///returnCode: char*
public delegate uint TS3Functions_requestSendClientQueryCommand(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string command, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: char**
public delegate uint TS3Functions_getTransferFileName(ushort transferID, ref System.IntPtr result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: char**
public delegate uint TS3Functions_getTransferFilePath(ushort transferID, ref System.IntPtr result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: uint64*
public delegate uint TS3Functions_getTransferFileSize(ushort transferID, ref ulong result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: uint64*
public delegate uint TS3Functions_getTransferFileSizeDone(ushort transferID, ref ulong result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: int*
public delegate uint TS3Functions_isTransferSender(ushort transferID, ref int result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: int*
public delegate uint TS3Functions_getTransferStatus(ushort transferID, ref int result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: float*
public delegate uint TS3Functions_getCurrentTransferSpeed(ushort transferID, ref float result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: float*
public delegate uint TS3Functions_getAverageTransferSpeed(ushort transferID, ref float result);

/// Return Type: unsigned int
///transferID: anyID->unsigned short
///result: uint64*
public delegate uint TS3Functions_getTransferRunTime(ushort transferID, ref ulong result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPW: char*
///file: char*
///overwrite: int
///resume: int
///sourceDirectory: char*
///result: anyID*
///returnCode: char*
public delegate uint TS3Functions_sendFile(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string file, int overwrite, int resume, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string sourceDirectory, ref ushort result, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPW: char*
///file: char*
///overwrite: int
///resume: int
///destinationDirectory: char*
///result: anyID*
///returnCode: char*
public delegate uint TS3Functions_requestFile(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string file, int overwrite, int resume, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string destinationDirectory, ref ushort result, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///transferID: anyID->unsigned short
///deleteUnfinishedFile: int
///returnCode: char*
public delegate uint TS3Functions_haltTransfer(ulong serverConnectionHandlerID, ushort transferID, int deleteUnfinishedFile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPW: char*
///path: char*
///returnCode: char*
public delegate uint TS3Functions_requestFileList(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string path, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPW: char*
///file: char*
///returnCode: char*
public delegate uint TS3Functions_requestFileInfo(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string file, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPW: char*
///file: char**
///returnCode: char*
public delegate uint TS3Functions_requestDeleteFile(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, ref System.IntPtr file, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPW: char*
///directoryPath: char*
///returnCode: char*
public delegate uint TS3Functions_requestCreateDirectory(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string directoryPath, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///fromChannelID: uint64->unsigned __int64
///channelPW: char*
///toChannelID: uint64->unsigned __int64
///toChannelPW: char*
///oldFile: char*
///newFile: char*
///returnCode: char*
public delegate uint TS3Functions_requestRenameFile(ulong serverConnectionHandlerID, ulong fromChannelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPW, ulong toChannelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string toChannelPW, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string oldFile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string newFile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///toClientUID: char*
///subject: char*
///message: char*
///returnCode: char*
public delegate uint TS3Functions_requestMessageAdd(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string toClientUID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string subject, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///messageID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestMessageDel(ulong serverConnectionHandlerID, ulong messageID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///messageID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestMessageGet(ulong serverConnectionHandlerID, ulong messageID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestMessageList(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///messageID: uint64->unsigned __int64
///flag: int
///returnCode: char*
public delegate uint TS3Functions_requestMessageUpdateFlag(ulong serverConnectionHandlerID, ulong messageID, int flag, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverPassword: char*
///returnCode: char*
public delegate uint TS3Functions_verifyServerPassword(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///channelPassword: char*
///returnCode: char*
public delegate uint TS3Functions_verifyChannelPassword(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///timeInSeconds: uint64->unsigned __int64
///banReason: char*
///returnCode: char*
public delegate uint TS3Functions_banclient(ulong serverConnectionHandlerID, ushort clientID, ulong timeInSeconds, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string banReason, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///ipRegExp: char*
///nameRegexp: char*
///uniqueIdentity: char*
///timeInSeconds: uint64->unsigned __int64
///banReason: char*
///returnCode: char*
public delegate uint TS3Functions_banadd(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string ipRegExp, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string nameRegexp, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string uniqueIdentity, ulong timeInSeconds, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string banReason, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientDBID: uint64->unsigned __int64
///timeInSeconds: uint64->unsigned __int64
///banReason: char*
///returnCode: char*
public delegate uint TS3Functions_banclientdbid(ulong serverConnectionHandlerID, ulong clientDBID, ulong timeInSeconds, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string banReason, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///banID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_bandel(ulong serverConnectionHandlerID, ulong banID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_bandelall(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestBanList(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///targetClientDatabaseID: uint64->unsigned __int64
///complainReason: char*
///returnCode: char*
public delegate uint TS3Functions_requestComplainAdd(ulong serverConnectionHandlerID, ulong targetClientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string complainReason, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///targetClientDatabaseID: uint64->unsigned __int64
///fromClientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestComplainDel(ulong serverConnectionHandlerID, ulong targetClientDatabaseID, ulong fromClientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///targetClientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestComplainDelAll(ulong serverConnectionHandlerID, ulong targetClientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///targetClientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestComplainList(ulong serverConnectionHandlerID, ulong targetClientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupList(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///groupName: char*
///groupType: int
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupAdd(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string groupName, int groupType, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///force: int
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupDel(ulong serverConnectionHandlerID, ulong serverGroupID, int force, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupAddClient(ulong serverConnectionHandlerID, ulong serverGroupID, ulong clientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupDelClient(ulong serverConnectionHandlerID, ulong serverGroupID, ulong clientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupsByClientID(ulong serverConnectionHandlerID, ulong clientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///continueonerror: int
///permissionIDArray: int*
///permissionValueArray: int*
///permissionNegatedArray: int*
///permissionSkipArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupAddPerm(ulong serverConnectionHandlerID, ulong serverGroupID, int continueonerror, ref uint permissionIDArray, ref int permissionValueArray, ref int permissionNegatedArray, ref int permissionSkipArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///continueOnError: int
///permissionIDArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupDelPerm(ulong serverConnectionHandlerID, ulong serverGroupID, int continueOnError, ref uint permissionIDArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupPermList(ulong serverConnectionHandlerID, ulong serverGroupID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///serverGroupID: uint64->unsigned __int64
///withNames: int
///returnCode: char*
public delegate uint TS3Functions_requestServerGroupClientList(ulong serverConnectionHandlerID, ulong serverGroupID, int withNames, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelGroupList(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///groupName: char*
///groupType: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelGroupAdd(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string groupName, int groupType, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelGroupID: uint64->unsigned __int64
///force: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelGroupDel(ulong serverConnectionHandlerID, ulong channelGroupID, int force, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelGroupID: uint64->unsigned __int64
///continueonerror: int
///permissionIDArray: int*
///permissionValueArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelGroupAddPerm(ulong serverConnectionHandlerID, ulong channelGroupID, int continueonerror, ref uint permissionIDArray, ref int permissionValueArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelGroupID: uint64->unsigned __int64
///continueOnError: int
///permissionIDArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelGroupDelPerm(ulong serverConnectionHandlerID, ulong channelGroupID, int continueOnError, ref uint permissionIDArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelGroupID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelGroupPermList(ulong serverConnectionHandlerID, ulong channelGroupID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelGroupIDArray: uint64*
///channelIDArray: uint64*
///clientDatabaseIDArray: uint64*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestSetClientChannelGroup(ulong serverConnectionHandlerID, ref ulong channelGroupIDArray, ref ulong channelIDArray, ref ulong clientDatabaseIDArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///permissionIDArray: int*
///permissionValueArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelAddPerm(ulong serverConnectionHandlerID, ulong channelID, ref uint permissionIDArray, ref int permissionValueArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///permissionIDArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelDelPerm(ulong serverConnectionHandlerID, ulong channelID, ref uint permissionIDArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelPermList(ulong serverConnectionHandlerID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///permissionIDArray: int*
///permissionValueArray: int*
///permissionSkipArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestClientAddPerm(ulong serverConnectionHandlerID, ulong clientDatabaseID, ref uint permissionIDArray, ref int permissionValueArray, ref int permissionSkipArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///permissionIDArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestClientDelPerm(ulong serverConnectionHandlerID, ulong clientDatabaseID, ref uint permissionIDArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestClientPermList(ulong serverConnectionHandlerID, ulong clientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///permissionIDArray: int*
///permissionValueArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelClientAddPerm(ulong serverConnectionHandlerID, ulong channelID, ulong clientDatabaseID, ref uint permissionIDArray, ref int permissionValueArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///permissionIDArray: int*
///arraySize: int
///returnCode: char*
public delegate uint TS3Functions_requestChannelClientDelPerm(ulong serverConnectionHandlerID, ulong channelID, ulong clientDatabaseID, ref uint permissionIDArray, int arraySize, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///clientDatabaseID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestChannelClientPermList(ulong serverConnectionHandlerID, ulong channelID, ulong clientDatabaseID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandler: uint64->unsigned __int64
///tokenKey: char*
///returnCode: char*
public delegate uint TS3Functions_privilegeKeyUse(ulong serverConnectionHandler, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string tokenKey, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandler: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestPermissionList(ulong serverConnectionHandler, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///serverConnectionHandler: uint64->unsigned __int64
///clientDBID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///returnCode: char*
public delegate uint TS3Functions_requestPermissionOverview(ulong serverConnectionHandler, ulong clientDBID, ulong channelID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: unsigned int
///clientPropertyString: char*
///resultFlag: size_t*
public delegate uint TS3Functions_clientPropertyStringToFlag([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string clientPropertyString, ref uint resultFlag);

/// Return Type: unsigned int
///channelPropertyString: char*
///resultFlag: size_t*
public delegate uint TS3Functions_channelPropertyStringToFlag([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPropertyString, ref uint resultFlag);

/// Return Type: unsigned int
///serverPropertyString: char*
///resultFlag: size_t*
public delegate uint TS3Functions_serverPropertyStringToFlag([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverPropertyString, ref uint resultFlag);

/// Return Type: void
///path: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_getAppPath(System.IntPtr path, System.IntPtr maxLen);

/// Return Type: void
///path: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_getResourcesPath(System.IntPtr path, System.IntPtr maxLen);

/// Return Type: void
///path: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_getConfigPath(System.IntPtr path, System.IntPtr maxLen);

/// Return Type: void
///path: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_getPluginPath(System.IntPtr path, System.IntPtr maxLen);

/// Return Type: uint64->unsigned __int64
public delegate ulong TS3Functions_getCurrentServerConnectionHandlerID();

/// Return Type: void
///serverConnectionHandlerID: uint64->unsigned __int64
///message: char*
///messageTarget: PluginMessageTarget
public delegate void TS3Functions_printMessage(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message, PluginMessageTarget messageTarget);

/// Return Type: void
///message: char*
public delegate void TS3Functions_printMessageToCurrentTab([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string message);

/// Return Type: void
///text: char*
///result: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_urlsToBB([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string text, System.IntPtr result, System.IntPtr maxLen);

/// Return Type: void
///serverConnectionHandlerID: uint64->unsigned __int64
///pluginID: char*
///command: char*
///targetMode: int
///targetIDs: anyID*
///returnCode: char*
public delegate void TS3Functions_sendPluginCommand(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pluginID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string command, int targetMode, ref ushort targetIDs, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string returnCode);

/// Return Type: void
///path: char*
///result: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_getDirectories([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string path, System.IntPtr result, System.IntPtr maxLen);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///host: char*
///port: unsigned short*
///password: char*
///maxLen: size_t->unsigned int
public delegate uint TS3Functions_getServerConnectInfo(ulong scHandlerID, System.IntPtr host, ref ushort port, System.IntPtr password, System.IntPtr maxLen);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///channelID: uint64->unsigned __int64
///path: char*
///password: char*
///maxLen: size_t->unsigned int
public delegate uint TS3Functions_getChannelConnectInfo(ulong scHandlerID, ulong channelID, System.IntPtr path, System.IntPtr password, System.IntPtr maxLen);

/// Return Type: void
///pluginID: char*
///returnCode: char*
///maxLen: size_t->unsigned int
public delegate void TS3Functions_createReturnCode([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pluginID, System.IntPtr returnCode, System.IntPtr maxLen);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///itemType: PluginItemType
///itemID: uint64->unsigned __int64
public delegate uint TS3Functions_requestInfoUpdate(ulong scHandlerID, PluginItemType itemType, ulong itemID);

/// Return Type: uint64->unsigned __int64
///scHandlerID: uint64->unsigned __int64
public delegate ulong TS3Functions_getServerVersion(ulong scHandlerID);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///result: int*
public delegate uint TS3Functions_isWhispering(ulong scHandlerID, ushort clientID, ref int result);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///result: int*
public delegate uint TS3Functions_isReceivingWhisper(ulong scHandlerID, ushort clientID, ref int result);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///result: char*
///maxLen: size_t->unsigned int
public delegate uint TS3Functions_getAvatar(ulong scHandlerID, ushort clientID, System.IntPtr result, System.IntPtr maxLen);

/// Return Type: void
///pluginID: char*
///menuID: int
///enabled: int
public delegate void TS3Functions_setPluginMenuEnabled([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pluginID, int menuID, int enabled);

/// Return Type: void
public delegate void TS3Functions_showHotkeySetup();

/// Return Type: void
///pluginID: char*
///keyword: char*
///qParentWindow: void*
public delegate void TS3Functions_requestHotkeyInputDialog([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pluginID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string keyword, System.IntPtr qParentWindow);

/// Return Type: unsigned int
///pluginID: char*
///keywords: char**
///hotkeys: char**
///arrayLen: size_t->unsigned int
///hotkeyBufSize: size_t->unsigned int
public delegate uint TS3Functions_getHotkeyFromKeyword([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string pluginID, ref System.IntPtr keywords, ref System.IntPtr hotkeys, System.IntPtr arrayLen, System.IntPtr hotkeyBufSize);

/// Return Type: unsigned int
///scHandlerID: uint64->unsigned __int64
///clientID: anyID->unsigned short
///result: char*
///maxLen: size_t->unsigned int
public delegate uint TS3Functions_getClientDisplayName(ulong scHandlerID, ushort clientID, System.IntPtr result, System.IntPtr maxLen);

/// Return Type: unsigned int
///list: PluginBookmarkList**
public delegate uint TS3Functions_getBookmarkList(ref System.IntPtr list);

/// Return Type: unsigned int
///profile: PluginGuiProfile
///defaultProfileIdx: int*
///result: char***
public delegate uint TS3Functions_getProfileList(PluginGuiProfile profile, ref int defaultProfileIdx, ref System.IntPtr result);

/// Return Type: unsigned int
///connectTab: PluginConnectTab
///serverLabel: char*
///serverAddress: char*
///serverPassword: char*
///nickname: char*
///channel: char*
///channelPassword: char*
///captureProfile: char*
///playbackProfile: char*
///hotkeyProfile: char*
///soundProfile: char*
///userIdentity: char*
///oneTimeKey: char*
///phoneticName: char*
///scHandlerID: uint64*
public delegate uint TS3Functions_guiConnect(PluginConnectTab connectTab, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverLabel, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverAddress, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string nickname, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channel, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string captureProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string playbackProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string hotkeyProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string soundProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string userIdentity, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string oneTimeKey, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string phoneticName, ref ulong scHandlerID);

/// Return Type: unsigned int
///connectTab: PluginConnectTab
///bookmarkuuid: char*
///scHandlerID: uint64*
public delegate uint TS3Functions_guiConnectBookmark(PluginConnectTab connectTab, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string bookmarkuuid, ref ulong scHandlerID);

/// Return Type: unsigned int
///bookmarkuuid: char*
///serverLabel: char*
///serverAddress: char*
///serverPassword: char*
///nickname: char*
///channel: char*
///channelPassword: char*
///captureProfile: char*
///playbackProfile: char*
///hotkeyProfile: char*
///soundProfile: char*
///uniqueUserId: char*
///oneTimeKey: char*
///phoneticName: char*
public delegate uint TS3Functions_createBookmark([System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string bookmarkuuid, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverLabel, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverAddress, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string serverPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string nickname, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channel, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string channelPassword, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string captureProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string playbackProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string hotkeyProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string soundProfile, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string uniqueUserId, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string oneTimeKey, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string phoneticName);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///permissionName: char*
///result: unsigned int*
public delegate uint TS3Functions_getPermissionIDByName(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string permissionName, ref uint result);

/// Return Type: unsigned int
///serverConnectionHandlerID: uint64->unsigned __int64
///permissionName: char*
///result: int*
public delegate uint TS3Functions_getClientNeededPermission(ulong serverConnectionHandlerID, [System.Runtime.InteropServices.InAttribute()] [System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.LPStr)] string permissionName, ref int result);

[System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential)]
public struct TS3Functions
{

    /// TS3Functions_getClientLibVersion
    public TS3Functions_getClientLibVersion getClientLibVersion;

    /// TS3Functions_getClientLibVersionNumber
    public TS3Functions_getClientLibVersionNumber getClientLibVersionNumber;

    /// TS3Functions_spawnNewServerConnectionHandler
    public TS3Functions_spawnNewServerConnectionHandler spawnNewServerConnectionHandler;

    /// TS3Functions_destroyServerConnectionHandler
    public TS3Functions_destroyServerConnectionHandler destroyServerConnectionHandler;

    /// TS3Functions_getErrorMessage
    public TS3Functions_getErrorMessage getErrorMessage;

    /// TS3Functions_freeMemory
    public TS3Functions_freeMemory freeMemory;

    /// TS3Functions_logMessage
    public TS3Functions_logMessage logMessage;

    /// TS3Functions_getPlaybackDeviceList
    public TS3Functions_getPlaybackDeviceList getPlaybackDeviceList;

    /// TS3Functions_getPlaybackModeList
    public TS3Functions_getPlaybackModeList getPlaybackModeList;

    /// TS3Functions_getCaptureDeviceList
    public TS3Functions_getCaptureDeviceList getCaptureDeviceList;

    /// TS3Functions_getCaptureModeList
    public TS3Functions_getCaptureModeList getCaptureModeList;

    /// TS3Functions_getDefaultPlaybackDevice
    public TS3Functions_getDefaultPlaybackDevice getDefaultPlaybackDevice;

    /// TS3Functions_getDefaultPlayBackMode
    public TS3Functions_getDefaultPlayBackMode getDefaultPlayBackMode;

    /// TS3Functions_getDefaultCaptureDevice
    public TS3Functions_getDefaultCaptureDevice getDefaultCaptureDevice;

    /// TS3Functions_getDefaultCaptureMode
    public TS3Functions_getDefaultCaptureMode getDefaultCaptureMode;

    /// TS3Functions_openPlaybackDevice
    public TS3Functions_openPlaybackDevice openPlaybackDevice;

    /// TS3Functions_openCaptureDevice
    public TS3Functions_openCaptureDevice openCaptureDevice;

    /// TS3Functions_getCurrentPlaybackDeviceName
    public TS3Functions_getCurrentPlaybackDeviceName getCurrentPlaybackDeviceName;

    /// TS3Functions_getCurrentPlayBackMode
    public TS3Functions_getCurrentPlayBackMode getCurrentPlayBackMode;

    /// TS3Functions_getCurrentCaptureDeviceName
    public TS3Functions_getCurrentCaptureDeviceName getCurrentCaptureDeviceName;

    /// TS3Functions_getCurrentCaptureMode
    public TS3Functions_getCurrentCaptureMode getCurrentCaptureMode;

    /// TS3Functions_initiateGracefulPlaybackShutdown
    public TS3Functions_initiateGracefulPlaybackShutdown initiateGracefulPlaybackShutdown;

    /// TS3Functions_closePlaybackDevice
    public TS3Functions_closePlaybackDevice closePlaybackDevice;

    /// TS3Functions_closeCaptureDevice
    public TS3Functions_closeCaptureDevice closeCaptureDevice;

    /// TS3Functions_activateCaptureDevice
    public TS3Functions_activateCaptureDevice activateCaptureDevice;

    /// TS3Functions_playWaveFileHandle
    public TS3Functions_playWaveFileHandle playWaveFileHandle;

    /// TS3Functions_pauseWaveFileHandle
    public TS3Functions_pauseWaveFileHandle pauseWaveFileHandle;

    /// TS3Functions_closeWaveFileHandle
    public TS3Functions_closeWaveFileHandle closeWaveFileHandle;

    /// TS3Functions_playWaveFile
    public TS3Functions_playWaveFile playWaveFile;

    /// TS3Functions_registerCustomDevice
    public TS3Functions_registerCustomDevice registerCustomDevice;

    /// TS3Functions_unregisterCustomDevice
    public TS3Functions_unregisterCustomDevice unregisterCustomDevice;

    /// TS3Functions_processCustomCaptureData
    public TS3Functions_processCustomCaptureData processCustomCaptureData;

    /// TS3Functions_acquireCustomPlaybackData
    public TS3Functions_acquireCustomPlaybackData acquireCustomPlaybackData;

    /// TS3Functions_getPreProcessorInfoValueFloat
    public TS3Functions_getPreProcessorInfoValueFloat getPreProcessorInfoValueFloat;

    /// TS3Functions_getPreProcessorConfigValue
    public TS3Functions_getPreProcessorConfigValue getPreProcessorConfigValue;

    /// TS3Functions_setPreProcessorConfigValue
    public TS3Functions_setPreProcessorConfigValue setPreProcessorConfigValue;

    /// TS3Functions_getEncodeConfigValue
    public TS3Functions_getEncodeConfigValue getEncodeConfigValue;

    /// TS3Functions_getPlaybackConfigValueAsFloat
    public TS3Functions_getPlaybackConfigValueAsFloat getPlaybackConfigValueAsFloat;

    /// TS3Functions_setPlaybackConfigValue
    public TS3Functions_setPlaybackConfigValue setPlaybackConfigValue;

    /// TS3Functions_setClientVolumeModifier
    public TS3Functions_setClientVolumeModifier setClientVolumeModifier;

    /// TS3Functions_startVoiceRecording
    public TS3Functions_startVoiceRecording startVoiceRecording;

    /// TS3Functions_stopVoiceRecording
    public TS3Functions_stopVoiceRecording stopVoiceRecording;

    /// TS3Functions_systemset3DListenerAttributes
    public TS3Functions_systemset3DListenerAttributes systemset3DListenerAttributes;

    /// TS3Functions_set3DWaveAttributes
    public TS3Functions_set3DWaveAttributes set3DWaveAttributes;

    /// TS3Functions_systemset3DSettings
    public TS3Functions_systemset3DSettings systemset3DSettings;

    /// TS3Functions_channelset3DAttributes
    public TS3Functions_channelset3DAttributes channelset3DAttributes;

    /// TS3Functions_startConnection
    public TS3Functions_startConnection startConnection;

    /// TS3Functions_stopConnection
    public TS3Functions_stopConnection stopConnection;

    /// TS3Functions_requestClientMove
    public TS3Functions_requestClientMove requestClientMove;

    /// TS3Functions_requestClientVariables
    public TS3Functions_requestClientVariables requestClientVariables;

    /// TS3Functions_requestClientKickFromChannel
    public TS3Functions_requestClientKickFromChannel requestClientKickFromChannel;

    /// TS3Functions_requestClientKickFromServer
    public TS3Functions_requestClientKickFromServer requestClientKickFromServer;

    /// TS3Functions_requestChannelDelete
    public TS3Functions_requestChannelDelete requestChannelDelete;

    /// TS3Functions_requestChannelMove
    public TS3Functions_requestChannelMove requestChannelMove;

    /// TS3Functions_requestSendPrivateTextMsg
    public TS3Functions_requestSendPrivateTextMsg requestSendPrivateTextMsg;

    /// TS3Functions_requestSendChannelTextMsg
    public TS3Functions_requestSendChannelTextMsg requestSendChannelTextMsg;

    /// TS3Functions_requestSendServerTextMsg
    public TS3Functions_requestSendServerTextMsg requestSendServerTextMsg;

    /// TS3Functions_requestConnectionInfo
    public TS3Functions_requestConnectionInfo requestConnectionInfo;

    /// TS3Functions_requestClientSetWhisperList
    public TS3Functions_requestClientSetWhisperList requestClientSetWhisperList;

    /// TS3Functions_requestChannelSubscribe
    public TS3Functions_requestChannelSubscribe requestChannelSubscribe;

    /// TS3Functions_requestChannelSubscribeAll
    public TS3Functions_requestChannelSubscribeAll requestChannelSubscribeAll;

    /// TS3Functions_requestChannelUnsubscribe
    public TS3Functions_requestChannelUnsubscribe requestChannelUnsubscribe;

    /// TS3Functions_requestChannelUnsubscribeAll
    public TS3Functions_requestChannelUnsubscribeAll requestChannelUnsubscribeAll;

    /// TS3Functions_requestChannelDescription
    public TS3Functions_requestChannelDescription requestChannelDescription;

    /// TS3Functions_requestMuteClients
    public TS3Functions_requestMuteClients requestMuteClients;

    /// TS3Functions_requestUnmuteClients
    public TS3Functions_requestUnmuteClients requestUnmuteClients;

    /// TS3Functions_requestClientPoke
    public TS3Functions_requestClientPoke requestClientPoke;

    /// TS3Functions_requestClientIDs
    public TS3Functions_requestClientIDs requestClientIDs;

    /// TS3Functions_clientChatClosed
    public TS3Functions_clientChatClosed clientChatClosed;

    /// TS3Functions_clientChatComposing
    public TS3Functions_clientChatComposing clientChatComposing;

    /// TS3Functions_requestServerTemporaryPasswordAdd
    public TS3Functions_requestServerTemporaryPasswordAdd requestServerTemporaryPasswordAdd;

    /// TS3Functions_requestServerTemporaryPasswordDel
    public TS3Functions_requestServerTemporaryPasswordDel requestServerTemporaryPasswordDel;

    /// TS3Functions_requestServerTemporaryPasswordList
    public TS3Functions_requestServerTemporaryPasswordList requestServerTemporaryPasswordList;

    /// TS3Functions_getClientID
    public TS3Functions_getClientID getClientID;

    /// TS3Functions_getClientSelfVariableAsInt
    public TS3Functions_getClientSelfVariableAsInt getClientSelfVariableAsInt;

    /// TS3Functions_getClientSelfVariableAsString
    public TS3Functions_getClientSelfVariableAsString getClientSelfVariableAsString;

    /// TS3Functions_setClientSelfVariableAsInt
    public TS3Functions_setClientSelfVariableAsInt setClientSelfVariableAsInt;

    /// TS3Functions_setClientSelfVariableAsString
    public TS3Functions_setClientSelfVariableAsString setClientSelfVariableAsString;

    /// TS3Functions_flushClientSelfUpdates
    public TS3Functions_flushClientSelfUpdates flushClientSelfUpdates;

    /// TS3Functions_getClientVariableAsInt
    public TS3Functions_getClientVariableAsInt getClientVariableAsInt;

    /// TS3Functions_getClientVariableAsUInt64
    public TS3Functions_getClientVariableAsUInt64 getClientVariableAsUInt64;

    /// TS3Functions_getClientVariableAsString
    public TS3Functions_getClientVariableAsString getClientVariableAsString;

    /// TS3Functions_getClientList
    public TS3Functions_getClientList getClientList;

    /// TS3Functions_getChannelOfClient
    public TS3Functions_getChannelOfClient getChannelOfClient;

    /// TS3Functions_getChannelVariableAsInt
    public TS3Functions_getChannelVariableAsInt getChannelVariableAsInt;

    /// TS3Functions_getChannelVariableAsUInt64
    public TS3Functions_getChannelVariableAsUInt64 getChannelVariableAsUInt64;

    /// TS3Functions_getChannelVariableAsString
    public TS3Functions_getChannelVariableAsString getChannelVariableAsString;

    /// TS3Functions_getChannelIDFromChannelNames
    public TS3Functions_getChannelIDFromChannelNames getChannelIDFromChannelNames;

    /// TS3Functions_setChannelVariableAsInt
    public TS3Functions_setChannelVariableAsInt setChannelVariableAsInt;

    /// TS3Functions_setChannelVariableAsUInt64
    public TS3Functions_setChannelVariableAsUInt64 setChannelVariableAsUInt64;

    /// TS3Functions_setChannelVariableAsString
    public TS3Functions_setChannelVariableAsString setChannelVariableAsString;

    /// TS3Functions_flushChannelUpdates
    public TS3Functions_flushChannelUpdates flushChannelUpdates;

    /// TS3Functions_flushChannelCreation
    public TS3Functions_flushChannelCreation flushChannelCreation;

    /// TS3Functions_getChannelList
    public TS3Functions_getChannelList getChannelList;

    /// TS3Functions_getChannelClientList
    public TS3Functions_getChannelClientList getChannelClientList;

    /// TS3Functions_getParentChannelOfChannel
    public TS3Functions_getParentChannelOfChannel getParentChannelOfChannel;

    /// TS3Functions_getServerConnectionHandlerList
    public TS3Functions_getServerConnectionHandlerList getServerConnectionHandlerList;

    /// TS3Functions_getServerVariableAsInt
    public TS3Functions_getServerVariableAsInt getServerVariableAsInt;

    /// TS3Functions_getServerVariableAsUInt64
    public TS3Functions_getServerVariableAsUInt64 getServerVariableAsUInt64;

    /// TS3Functions_getServerVariableAsString
    public TS3Functions_getServerVariableAsString getServerVariableAsString;

    /// TS3Functions_requestServerVariables
    public TS3Functions_requestServerVariables requestServerVariables;

    /// TS3Functions_getConnectionStatus
    public TS3Functions_getConnectionStatus getConnectionStatus;

    /// TS3Functions_getConnectionVariableAsUInt64
    public TS3Functions_getConnectionVariableAsUInt64 getConnectionVariableAsUInt64;

    /// TS3Functions_getConnectionVariableAsDouble
    public TS3Functions_getConnectionVariableAsDouble getConnectionVariableAsDouble;

    /// TS3Functions_getConnectionVariableAsString
    public TS3Functions_getConnectionVariableAsString getConnectionVariableAsString;

    /// TS3Functions_cleanUpConnectionInfo
    public TS3Functions_cleanUpConnectionInfo cleanUpConnectionInfo;

    /// TS3Functions_requestClientDBIDfromUID
    public TS3Functions_requestClientDBIDfromUID requestClientDBIDfromUID;

    /// TS3Functions_requestClientNamefromUID
    public TS3Functions_requestClientNamefromUID requestClientNamefromUID;

    /// TS3Functions_requestClientNamefromDBID
    public TS3Functions_requestClientNamefromDBID requestClientNamefromDBID;

    /// TS3Functions_requestClientEditDescription
    public TS3Functions_requestClientEditDescription requestClientEditDescription;

    /// TS3Functions_requestClientSetIsTalker
    public TS3Functions_requestClientSetIsTalker requestClientSetIsTalker;

    /// TS3Functions_requestIsTalker
    public TS3Functions_requestIsTalker requestIsTalker;

    /// TS3Functions_requestSendClientQueryCommand
    public TS3Functions_requestSendClientQueryCommand requestSendClientQueryCommand;

    /// TS3Functions_getTransferFileName
    public TS3Functions_getTransferFileName getTransferFileName;

    /// TS3Functions_getTransferFilePath
    public TS3Functions_getTransferFilePath getTransferFilePath;

    /// TS3Functions_getTransferFileSize
    public TS3Functions_getTransferFileSize getTransferFileSize;

    /// TS3Functions_getTransferFileSizeDone
    public TS3Functions_getTransferFileSizeDone getTransferFileSizeDone;

    /// TS3Functions_isTransferSender
    public TS3Functions_isTransferSender isTransferSender;

    /// TS3Functions_getTransferStatus
    public TS3Functions_getTransferStatus getTransferStatus;

    /// TS3Functions_getCurrentTransferSpeed
    public TS3Functions_getCurrentTransferSpeed getCurrentTransferSpeed;

    /// TS3Functions_getAverageTransferSpeed
    public TS3Functions_getAverageTransferSpeed getAverageTransferSpeed;

    /// TS3Functions_getTransferRunTime
    public TS3Functions_getTransferRunTime getTransferRunTime;

    /// TS3Functions_sendFile
    public TS3Functions_sendFile sendFile;

    /// TS3Functions_requestFile
    public TS3Functions_requestFile requestFile;

    /// TS3Functions_haltTransfer
    public TS3Functions_haltTransfer haltTransfer;

    /// TS3Functions_requestFileList
    public TS3Functions_requestFileList requestFileList;

    /// TS3Functions_requestFileInfo
    public TS3Functions_requestFileInfo requestFileInfo;

    /// TS3Functions_requestDeleteFile
    public TS3Functions_requestDeleteFile requestDeleteFile;

    /// TS3Functions_requestCreateDirectory
    public TS3Functions_requestCreateDirectory requestCreateDirectory;

    /// TS3Functions_requestRenameFile
    public TS3Functions_requestRenameFile requestRenameFile;

    /// TS3Functions_requestMessageAdd
    public TS3Functions_requestMessageAdd requestMessageAdd;

    /// TS3Functions_requestMessageDel
    public TS3Functions_requestMessageDel requestMessageDel;

    /// TS3Functions_requestMessageGet
    public TS3Functions_requestMessageGet requestMessageGet;

    /// TS3Functions_requestMessageList
    public TS3Functions_requestMessageList requestMessageList;

    /// TS3Functions_requestMessageUpdateFlag
    public TS3Functions_requestMessageUpdateFlag requestMessageUpdateFlag;

    /// TS3Functions_verifyServerPassword
    public TS3Functions_verifyServerPassword verifyServerPassword;

    /// TS3Functions_verifyChannelPassword
    public TS3Functions_verifyChannelPassword verifyChannelPassword;

    /// TS3Functions_banclient
    public TS3Functions_banclient banclient;

    /// TS3Functions_banadd
    public TS3Functions_banadd banadd;

    /// TS3Functions_banclientdbid
    public TS3Functions_banclientdbid banclientdbid;

    /// TS3Functions_bandel
    public TS3Functions_bandel bandel;

    /// TS3Functions_bandelall
    public TS3Functions_bandelall bandelall;

    /// TS3Functions_requestBanList
    public TS3Functions_requestBanList requestBanList;

    /// TS3Functions_requestComplainAdd
    public TS3Functions_requestComplainAdd requestComplainAdd;

    /// TS3Functions_requestComplainDel
    public TS3Functions_requestComplainDel requestComplainDel;

    /// TS3Functions_requestComplainDelAll
    public TS3Functions_requestComplainDelAll requestComplainDelAll;

    /// TS3Functions_requestComplainList
    public TS3Functions_requestComplainList requestComplainList;

    /// TS3Functions_requestServerGroupList
    public TS3Functions_requestServerGroupList requestServerGroupList;

    /// TS3Functions_requestServerGroupAdd
    public TS3Functions_requestServerGroupAdd requestServerGroupAdd;

    /// TS3Functions_requestServerGroupDel
    public TS3Functions_requestServerGroupDel requestServerGroupDel;

    /// TS3Functions_requestServerGroupAddClient
    public TS3Functions_requestServerGroupAddClient requestServerGroupAddClient;

    /// TS3Functions_requestServerGroupDelClient
    public TS3Functions_requestServerGroupDelClient requestServerGroupDelClient;

    /// TS3Functions_requestServerGroupsByClientID
    public TS3Functions_requestServerGroupsByClientID requestServerGroupsByClientID;

    /// TS3Functions_requestServerGroupAddPerm
    public TS3Functions_requestServerGroupAddPerm requestServerGroupAddPerm;

    /// TS3Functions_requestServerGroupDelPerm
    public TS3Functions_requestServerGroupDelPerm requestServerGroupDelPerm;

    /// TS3Functions_requestServerGroupPermList
    public TS3Functions_requestServerGroupPermList requestServerGroupPermList;

    /// TS3Functions_requestServerGroupClientList
    public TS3Functions_requestServerGroupClientList requestServerGroupClientList;

    /// TS3Functions_requestChannelGroupList
    public TS3Functions_requestChannelGroupList requestChannelGroupList;

    /// TS3Functions_requestChannelGroupAdd
    public TS3Functions_requestChannelGroupAdd requestChannelGroupAdd;

    /// TS3Functions_requestChannelGroupDel
    public TS3Functions_requestChannelGroupDel requestChannelGroupDel;

    /// TS3Functions_requestChannelGroupAddPerm
    public TS3Functions_requestChannelGroupAddPerm requestChannelGroupAddPerm;

    /// TS3Functions_requestChannelGroupDelPerm
    public TS3Functions_requestChannelGroupDelPerm requestChannelGroupDelPerm;

    /// TS3Functions_requestChannelGroupPermList
    public TS3Functions_requestChannelGroupPermList requestChannelGroupPermList;

    /// TS3Functions_requestSetClientChannelGroup
    public TS3Functions_requestSetClientChannelGroup requestSetClientChannelGroup;

    /// TS3Functions_requestChannelAddPerm
    public TS3Functions_requestChannelAddPerm requestChannelAddPerm;

    /// TS3Functions_requestChannelDelPerm
    public TS3Functions_requestChannelDelPerm requestChannelDelPerm;

    /// TS3Functions_requestChannelPermList
    public TS3Functions_requestChannelPermList requestChannelPermList;

    /// TS3Functions_requestClientAddPerm
    public TS3Functions_requestClientAddPerm requestClientAddPerm;

    /// TS3Functions_requestClientDelPerm
    public TS3Functions_requestClientDelPerm requestClientDelPerm;

    /// TS3Functions_requestClientPermList
    public TS3Functions_requestClientPermList requestClientPermList;

    /// TS3Functions_requestChannelClientAddPerm
    public TS3Functions_requestChannelClientAddPerm requestChannelClientAddPerm;

    /// TS3Functions_requestChannelClientDelPerm
    public TS3Functions_requestChannelClientDelPerm requestChannelClientDelPerm;

    /// TS3Functions_requestChannelClientPermList
    public TS3Functions_requestChannelClientPermList requestChannelClientPermList;

    /// TS3Functions_privilegeKeyUse
    public TS3Functions_privilegeKeyUse privilegeKeyUse;

    /// TS3Functions_requestPermissionList
    public TS3Functions_requestPermissionList requestPermissionList;

    /// TS3Functions_requestPermissionOverview
    public TS3Functions_requestPermissionOverview requestPermissionOverview;

    /// TS3Functions_clientPropertyStringToFlag
    public TS3Functions_clientPropertyStringToFlag clientPropertyStringToFlag;

    /// TS3Functions_channelPropertyStringToFlag
    public TS3Functions_channelPropertyStringToFlag channelPropertyStringToFlag;

    /// TS3Functions_serverPropertyStringToFlag
    public TS3Functions_serverPropertyStringToFlag serverPropertyStringToFlag;

    /// TS3Functions_getAppPath
    public TS3Functions_getAppPath getAppPath;

    /// TS3Functions_getResourcesPath
    public TS3Functions_getResourcesPath getResourcesPath;

    /// TS3Functions_getConfigPath
    public TS3Functions_getConfigPath getConfigPath;

    /// TS3Functions_getPluginPath
    public TS3Functions_getPluginPath getPluginPath;

    /// TS3Functions_getCurrentServerConnectionHandlerID
    public TS3Functions_getCurrentServerConnectionHandlerID getCurrentServerConnectionHandlerID;

    /// TS3Functions_printMessage
    public TS3Functions_printMessage printMessage;

    /// TS3Functions_printMessageToCurrentTab
    public TS3Functions_printMessageToCurrentTab printMessageToCurrentTab;

    /// TS3Functions_urlsToBB
    public TS3Functions_urlsToBB urlsToBB;

    /// TS3Functions_sendPluginCommand
    public TS3Functions_sendPluginCommand sendPluginCommand;

    /// TS3Functions_getDirectories
    public TS3Functions_getDirectories getDirectories;

    /// TS3Functions_getServerConnectInfo
    public TS3Functions_getServerConnectInfo getServerConnectInfo;

    /// TS3Functions_getChannelConnectInfo
    public TS3Functions_getChannelConnectInfo getChannelConnectInfo;

    /// TS3Functions_createReturnCode
    public TS3Functions_createReturnCode createReturnCode;

    /// TS3Functions_requestInfoUpdate
    public TS3Functions_requestInfoUpdate requestInfoUpdate;

    /// TS3Functions_getServerVersion
    public TS3Functions_getServerVersion getServerVersion;

    /// TS3Functions_isWhispering
    public TS3Functions_isWhispering isWhispering;

    /// TS3Functions_isReceivingWhisper
    public TS3Functions_isReceivingWhisper isReceivingWhisper;

    /// TS3Functions_getAvatar
    public TS3Functions_getAvatar getAvatar;

    /// TS3Functions_setPluginMenuEnabled
    public TS3Functions_setPluginMenuEnabled setPluginMenuEnabled;

    /// TS3Functions_showHotkeySetup
    public TS3Functions_showHotkeySetup showHotkeySetup;

    /// TS3Functions_requestHotkeyInputDialog
    public TS3Functions_requestHotkeyInputDialog requestHotkeyInputDialog;

    /// TS3Functions_getHotkeyFromKeyword
    public TS3Functions_getHotkeyFromKeyword getHotkeyFromKeyword;

    /// TS3Functions_getClientDisplayName
    public TS3Functions_getClientDisplayName getClientDisplayName;

    /// TS3Functions_getBookmarkList
    public TS3Functions_getBookmarkList getBookmarkList;

    /// TS3Functions_getProfileList
    public TS3Functions_getProfileList getProfileList;

    /// TS3Functions_guiConnect
    public TS3Functions_guiConnect guiConnect;

    /// TS3Functions_guiConnectBookmark
    public TS3Functions_guiConnectBookmark guiConnectBookmark;

    /// TS3Functions_createBookmark
    public TS3Functions_createBookmark createBookmark;

    /// TS3Functions_getPermissionIDByName
    public TS3Functions_getPermissionIDByName getPermissionIDByName;

    /// TS3Functions_getClientNeededPermission
    public TS3Functions_getClientNeededPermission getClientNeededPermission;
}



/*
public struct TS3Functions {
    
    /// TS3Functions_getClientLibVersion
    public TS3Functions_getClientLibVersion AnonymousMember1;
    
    /// TS3Functions_getClientLibVersionNumber
    public TS3Functions_getClientLibVersionNumber AnonymousMember2;
    
    /// TS3Functions_spawnNewServerConnectionHandler
    public TS3Functions_spawnNewServerConnectionHandler AnonymousMember3;
    
    /// TS3Functions_destroyServerConnectionHandler
    public TS3Functions_destroyServerConnectionHandler AnonymousMember4;
    
    /// TS3Functions_getErrorMessage
    public TS3Functions_getErrorMessage AnonymousMember5;
    
    /// TS3Functions_freeMemory
    public TS3Functions_freeMemory AnonymousMember6;
    
    /// TS3Functions_logMessage
    public TS3Functions_logMessage AnonymousMember7;
    
    /// TS3Functions_getPlaybackDeviceList
    public TS3Functions_getPlaybackDeviceList AnonymousMember8;
    
    /// TS3Functions_getPlaybackModeList
    public TS3Functions_getPlaybackModeList AnonymousMember9;
    
    /// TS3Functions_getCaptureDeviceList
    public TS3Functions_getCaptureDeviceList AnonymousMember10;
    
    /// TS3Functions_getCaptureModeList
    public TS3Functions_getCaptureModeList AnonymousMember11;
    
    /// TS3Functions_getDefaultPlaybackDevice
    public TS3Functions_getDefaultPlaybackDevice AnonymousMember12;
    
    /// TS3Functions_getDefaultPlayBackMode
    public TS3Functions_getDefaultPlayBackMode AnonymousMember13;
    
    /// TS3Functions_getDefaultCaptureDevice
    public TS3Functions_getDefaultCaptureDevice AnonymousMember14;
    
    /// TS3Functions_getDefaultCaptureMode
    public TS3Functions_getDefaultCaptureMode AnonymousMember15;
    
    /// TS3Functions_openPlaybackDevice
    public TS3Functions_openPlaybackDevice AnonymousMember16;
    
    /// TS3Functions_openCaptureDevice
    public TS3Functions_openCaptureDevice AnonymousMember17;
    
    /// TS3Functions_getCurrentPlaybackDeviceName
    public TS3Functions_getCurrentPlaybackDeviceName AnonymousMember18;
    
    /// TS3Functions_getCurrentPlayBackMode
    public TS3Functions_getCurrentPlayBackMode AnonymousMember19;
    
    /// TS3Functions_getCurrentCaptureDeviceName
    public TS3Functions_getCurrentCaptureDeviceName AnonymousMember20;
    
    /// TS3Functions_getCurrentCaptureMode
    public TS3Functions_getCurrentCaptureMode AnonymousMember21;
    
    /// TS3Functions_initiateGracefulPlaybackShutdown
    public TS3Functions_initiateGracefulPlaybackShutdown AnonymousMember22;
    
    /// TS3Functions_closePlaybackDevice
    public TS3Functions_closePlaybackDevice AnonymousMember23;
    
    /// TS3Functions_closeCaptureDevice
    public TS3Functions_closeCaptureDevice AnonymousMember24;
    
    /// TS3Functions_activateCaptureDevice
    public TS3Functions_activateCaptureDevice AnonymousMember25;
    
    /// TS3Functions_playWaveFileHandle
    public TS3Functions_playWaveFileHandle AnonymousMember26;
    
    /// TS3Functions_pauseWaveFileHandle
    public TS3Functions_pauseWaveFileHandle AnonymousMember27;
    
    /// TS3Functions_closeWaveFileHandle
    public TS3Functions_closeWaveFileHandle AnonymousMember28;
    
    /// TS3Functions_playWaveFile
    public TS3Functions_playWaveFile AnonymousMember29;
    
    /// TS3Functions_registerCustomDevice
    public TS3Functions_registerCustomDevice AnonymousMember30;
    
    /// TS3Functions_unregisterCustomDevice
    public TS3Functions_unregisterCustomDevice AnonymousMember31;
    
    /// TS3Functions_processCustomCaptureData
    public TS3Functions_processCustomCaptureData AnonymousMember32;
    
    /// TS3Functions_acquireCustomPlaybackData
    public TS3Functions_acquireCustomPlaybackData AnonymousMember33;
    
    /// TS3Functions_getPreProcessorInfoValueFloat
    public TS3Functions_getPreProcessorInfoValueFloat AnonymousMember34;
    
    /// TS3Functions_getPreProcessorConfigValue
    public TS3Functions_getPreProcessorConfigValue AnonymousMember35;
    
    /// TS3Functions_setPreProcessorConfigValue
    public TS3Functions_setPreProcessorConfigValue AnonymousMember36;
    
    /// TS3Functions_getEncodeConfigValue
    public TS3Functions_getEncodeConfigValue AnonymousMember37;
    
    /// TS3Functions_getPlaybackConfigValueAsFloat
    public TS3Functions_getPlaybackConfigValueAsFloat AnonymousMember38;
    
    /// TS3Functions_setPlaybackConfigValue
    public TS3Functions_setPlaybackConfigValue AnonymousMember39;
    
    /// TS3Functions_setClientVolumeModifier
    public TS3Functions_setClientVolumeModifier AnonymousMember40;
    
    /// TS3Functions_startVoiceRecording
    public TS3Functions_startVoiceRecording AnonymousMember41;
    
    /// TS3Functions_stopVoiceRecording
    public TS3Functions_stopVoiceRecording AnonymousMember42;
    
    /// TS3Functions_systemset3DListenerAttributes
    public TS3Functions_systemset3DListenerAttributes AnonymousMember43;
    
    /// TS3Functions_set3DWaveAttributes
    public TS3Functions_set3DWaveAttributes AnonymousMember44;
    
    /// TS3Functions_systemset3DSettings
    public TS3Functions_systemset3DSettings AnonymousMember45;
    
    /// TS3Functions_channelset3DAttributes
    public TS3Functions_channelset3DAttributes AnonymousMember46;
    
    /// TS3Functions_startConnection
    public TS3Functions_startConnection AnonymousMember47;
    
    /// TS3Functions_stopConnection
    public TS3Functions_stopConnection AnonymousMember48;
    
    /// TS3Functions_requestClientMove
    public TS3Functions_requestClientMove AnonymousMember49;
    
    /// TS3Functions_requestClientVariables
    public TS3Functions_requestClientVariables AnonymousMember50;
    
    /// TS3Functions_requestClientKickFromChannel
    public TS3Functions_requestClientKickFromChannel AnonymousMember51;
    
    /// TS3Functions_requestClientKickFromServer
    public TS3Functions_requestClientKickFromServer AnonymousMember52;
    
    /// TS3Functions_requestChannelDelete
    public TS3Functions_requestChannelDelete AnonymousMember53;
    
    /// TS3Functions_requestChannelMove
    public TS3Functions_requestChannelMove AnonymousMember54;
    
    /// TS3Functions_requestSendPrivateTextMsg
    public TS3Functions_requestSendPrivateTextMsg AnonymousMember55;
    
    /// TS3Functions_requestSendChannelTextMsg
    public TS3Functions_requestSendChannelTextMsg AnonymousMember56;
    
    /// TS3Functions_requestSendServerTextMsg
    public TS3Functions_requestSendServerTextMsg AnonymousMember57;
    
    /// TS3Functions_requestConnectionInfo
    public TS3Functions_requestConnectionInfo AnonymousMember58;
    
    /// TS3Functions_requestClientSetWhisperList
    public TS3Functions_requestClientSetWhisperList AnonymousMember59;
    
    /// TS3Functions_requestChannelSubscribe
    public TS3Functions_requestChannelSubscribe AnonymousMember60;
    
    /// TS3Functions_requestChannelSubscribeAll
    public TS3Functions_requestChannelSubscribeAll AnonymousMember61;
    
    /// TS3Functions_requestChannelUnsubscribe
    public TS3Functions_requestChannelUnsubscribe AnonymousMember62;
    
    /// TS3Functions_requestChannelUnsubscribeAll
    public TS3Functions_requestChannelUnsubscribeAll AnonymousMember63;
    
    /// TS3Functions_requestChannelDescription
    public TS3Functions_requestChannelDescription AnonymousMember64;
    
    /// TS3Functions_requestMuteClients
    public TS3Functions_requestMuteClients AnonymousMember65;
    
    /// TS3Functions_requestUnmuteClients
    public TS3Functions_requestUnmuteClients AnonymousMember66;
    
    /// TS3Functions_requestClientPoke
    public TS3Functions_requestClientPoke AnonymousMember67;
    
    /// TS3Functions_requestClientIDs
    public TS3Functions_requestClientIDs AnonymousMember68;
    
    /// TS3Functions_clientChatClosed
    public TS3Functions_clientChatClosed AnonymousMember69;
    
    /// TS3Functions_clientChatComposing
    public TS3Functions_clientChatComposing AnonymousMember70;
    
    /// TS3Functions_requestServerTemporaryPasswordAdd
    public TS3Functions_requestServerTemporaryPasswordAdd AnonymousMember71;
    
    /// TS3Functions_requestServerTemporaryPasswordDel
    public TS3Functions_requestServerTemporaryPasswordDel AnonymousMember72;
    
    /// TS3Functions_requestServerTemporaryPasswordList
    public TS3Functions_requestServerTemporaryPasswordList AnonymousMember73;
    
    /// TS3Functions_getClientID
    public TS3Functions_getClientID AnonymousMember74;
    
    /// TS3Functions_getClientSelfVariableAsInt
    public TS3Functions_getClientSelfVariableAsInt AnonymousMember75;
    
    /// TS3Functions_getClientSelfVariableAsString
    public TS3Functions_getClientSelfVariableAsString AnonymousMember76;
    
    /// TS3Functions_setClientSelfVariableAsInt
    public TS3Functions_setClientSelfVariableAsInt AnonymousMember77;
    
    /// TS3Functions_setClientSelfVariableAsString
    public TS3Functions_setClientSelfVariableAsString AnonymousMember78;
    
    /// TS3Functions_flushClientSelfUpdates
    public TS3Functions_flushClientSelfUpdates AnonymousMember79;
    
    /// TS3Functions_getClientVariableAsInt
    public TS3Functions_getClientVariableAsInt AnonymousMember80;
    
    /// TS3Functions_getClientVariableAsUInt64
    public TS3Functions_getClientVariableAsUInt64 AnonymousMember81;
    
    /// TS3Functions_getClientVariableAsString
    public TS3Functions_getClientVariableAsString AnonymousMember82;
    
    /// TS3Functions_getClientList
    public TS3Functions_getClientList AnonymousMember83;
    
    /// TS3Functions_getChannelOfClient
    public TS3Functions_getChannelOfClient AnonymousMember84;
    
    /// TS3Functions_getChannelVariableAsInt
    public TS3Functions_getChannelVariableAsInt AnonymousMember85;
    
    /// TS3Functions_getChannelVariableAsUInt64
    public TS3Functions_getChannelVariableAsUInt64 AnonymousMember86;
    
    /// TS3Functions_getChannelVariableAsString
    public TS3Functions_getChannelVariableAsString AnonymousMember87;
    
    /// TS3Functions_getChannelIDFromChannelNames
    public TS3Functions_getChannelIDFromChannelNames AnonymousMember88;
    
    /// TS3Functions_setChannelVariableAsInt
    public TS3Functions_setChannelVariableAsInt AnonymousMember89;
    
    /// TS3Functions_setChannelVariableAsUInt64
    public TS3Functions_setChannelVariableAsUInt64 AnonymousMember90;
    
    /// TS3Functions_setChannelVariableAsString
    public TS3Functions_setChannelVariableAsString AnonymousMember91;
    
    /// TS3Functions_flushChannelUpdates
    public TS3Functions_flushChannelUpdates AnonymousMember92;
    
    /// TS3Functions_flushChannelCreation
    public TS3Functions_flushChannelCreation AnonymousMember93;
    
    /// TS3Functions_getChannelList
    public TS3Functions_getChannelList AnonymousMember94;
    
    /// TS3Functions_getChannelClientList
    public TS3Functions_getChannelClientList AnonymousMember95;
    
    /// TS3Functions_getParentChannelOfChannel
    public TS3Functions_getParentChannelOfChannel AnonymousMember96;
    
    /// TS3Functions_getServerConnectionHandlerList
    public TS3Functions_getServerConnectionHandlerList AnonymousMember97;
    
    /// TS3Functions_getServerVariableAsInt
    public TS3Functions_getServerVariableAsInt AnonymousMember98;
    
    /// TS3Functions_getServerVariableAsUInt64
    public TS3Functions_getServerVariableAsUInt64 AnonymousMember99;
    
    /// TS3Functions_getServerVariableAsString
    public TS3Functions_getServerVariableAsString AnonymousMember100;
    
    /// TS3Functions_requestServerVariables
    public TS3Functions_requestServerVariables AnonymousMember101;
    
    /// TS3Functions_getConnectionStatus
    public TS3Functions_getConnectionStatus AnonymousMember102;
    
    /// TS3Functions_getConnectionVariableAsUInt64
    public TS3Functions_getConnectionVariableAsUInt64 AnonymousMember103;
    
    /// TS3Functions_getConnectionVariableAsDouble
    public TS3Functions_getConnectionVariableAsDouble AnonymousMember104;
    
    /// TS3Functions_getConnectionVariableAsString
    public TS3Functions_getConnectionVariableAsString AnonymousMember105;
    
    /// TS3Functions_cleanUpConnectionInfo
    public TS3Functions_cleanUpConnectionInfo AnonymousMember106;
    
    /// TS3Functions_requestClientDBIDfromUID
    public TS3Functions_requestClientDBIDfromUID AnonymousMember107;
    
    /// TS3Functions_requestClientNamefromUID
    public TS3Functions_requestClientNamefromUID AnonymousMember108;
    
    /// TS3Functions_requestClientNamefromDBID
    public TS3Functions_requestClientNamefromDBID AnonymousMember109;
    
    /// TS3Functions_requestClientEditDescription
    public TS3Functions_requestClientEditDescription AnonymousMember110;
    
    /// TS3Functions_requestClientSetIsTalker
    public TS3Functions_requestClientSetIsTalker AnonymousMember111;
    
    /// TS3Functions_requestIsTalker
    public TS3Functions_requestIsTalker AnonymousMember112;
    
    /// TS3Functions_requestSendClientQueryCommand
    public TS3Functions_requestSendClientQueryCommand AnonymousMember113;
    
    /// TS3Functions_getTransferFileName
    public TS3Functions_getTransferFileName AnonymousMember114;
    
    /// TS3Functions_getTransferFilePath
    public TS3Functions_getTransferFilePath AnonymousMember115;
    
    /// TS3Functions_getTransferFileSize
    public TS3Functions_getTransferFileSize AnonymousMember116;
    
    /// TS3Functions_getTransferFileSizeDone
    public TS3Functions_getTransferFileSizeDone AnonymousMember117;
    
    /// TS3Functions_isTransferSender
    public TS3Functions_isTransferSender AnonymousMember118;
    
    /// TS3Functions_getTransferStatus
    public TS3Functions_getTransferStatus AnonymousMember119;
    
    /// TS3Functions_getCurrentTransferSpeed
    public TS3Functions_getCurrentTransferSpeed AnonymousMember120;
    
    /// TS3Functions_getAverageTransferSpeed
    public TS3Functions_getAverageTransferSpeed AnonymousMember121;
    
    /// TS3Functions_getTransferRunTime
    public TS3Functions_getTransferRunTime AnonymousMember122;
    
    /// TS3Functions_sendFile
    public TS3Functions_sendFile AnonymousMember123;
    
    /// TS3Functions_requestFile
    public TS3Functions_requestFile AnonymousMember124;
    
    /// TS3Functions_haltTransfer
    public TS3Functions_haltTransfer AnonymousMember125;
    
    /// TS3Functions_requestFileList
    public TS3Functions_requestFileList AnonymousMember126;
    
    /// TS3Functions_requestFileInfo
    public TS3Functions_requestFileInfo AnonymousMember127;
    
    /// TS3Functions_requestDeleteFile
    public TS3Functions_requestDeleteFile AnonymousMember128;
    
    /// TS3Functions_requestCreateDirectory
    public TS3Functions_requestCreateDirectory AnonymousMember129;
    
    /// TS3Functions_requestRenameFile
    public TS3Functions_requestRenameFile AnonymousMember130;
    
    /// TS3Functions_requestMessageAdd
    public TS3Functions_requestMessageAdd AnonymousMember131;
    
    /// TS3Functions_requestMessageDel
    public TS3Functions_requestMessageDel AnonymousMember132;
    
    /// TS3Functions_requestMessageGet
    public TS3Functions_requestMessageGet AnonymousMember133;
    
    /// TS3Functions_requestMessageList
    public TS3Functions_requestMessageList AnonymousMember134;
    
    /// TS3Functions_requestMessageUpdateFlag
    public TS3Functions_requestMessageUpdateFlag AnonymousMember135;
    
    /// TS3Functions_verifyServerPassword
    public TS3Functions_verifyServerPassword AnonymousMember136;
    
    /// TS3Functions_verifyChannelPassword
    public TS3Functions_verifyChannelPassword AnonymousMember137;
    
    /// TS3Functions_banclient
    public TS3Functions_banclient AnonymousMember138;
    
    /// TS3Functions_banadd
    public TS3Functions_banadd AnonymousMember139;
    
    /// TS3Functions_banclientdbid
    public TS3Functions_banclientdbid AnonymousMember140;
    
    /// TS3Functions_bandel
    public TS3Functions_bandel AnonymousMember141;
    
    /// TS3Functions_bandelall
    public TS3Functions_bandelall AnonymousMember142;
    
    /// TS3Functions_requestBanList
    public TS3Functions_requestBanList AnonymousMember143;
    
    /// TS3Functions_requestComplainAdd
    public TS3Functions_requestComplainAdd AnonymousMember144;
    
    /// TS3Functions_requestComplainDel
    public TS3Functions_requestComplainDel AnonymousMember145;
    
    /// TS3Functions_requestComplainDelAll
    public TS3Functions_requestComplainDelAll AnonymousMember146;
    
    /// TS3Functions_requestComplainList
    public TS3Functions_requestComplainList AnonymousMember147;
    
    /// TS3Functions_requestServerGroupList
    public TS3Functions_requestServerGroupList AnonymousMember148;
    
    /// TS3Functions_requestServerGroupAdd
    public TS3Functions_requestServerGroupAdd AnonymousMember149;
    
    /// TS3Functions_requestServerGroupDel
    public TS3Functions_requestServerGroupDel AnonymousMember150;
    
    /// TS3Functions_requestServerGroupAddClient
    public TS3Functions_requestServerGroupAddClient AnonymousMember151;
    
    /// TS3Functions_requestServerGroupDelClient
    public TS3Functions_requestServerGroupDelClient AnonymousMember152;
    
    /// TS3Functions_requestServerGroupsByClientID
    public TS3Functions_requestServerGroupsByClientID AnonymousMember153;
    
    /// TS3Functions_requestServerGroupAddPerm
    public TS3Functions_requestServerGroupAddPerm AnonymousMember154;
    
    /// TS3Functions_requestServerGroupDelPerm
    public TS3Functions_requestServerGroupDelPerm AnonymousMember155;
    
    /// TS3Functions_requestServerGroupPermList
    public TS3Functions_requestServerGroupPermList AnonymousMember156;
    
    /// TS3Functions_requestServerGroupClientList
    public TS3Functions_requestServerGroupClientList AnonymousMember157;
    
    /// TS3Functions_requestChannelGroupList
    public TS3Functions_requestChannelGroupList AnonymousMember158;
    
    /// TS3Functions_requestChannelGroupAdd
    public TS3Functions_requestChannelGroupAdd AnonymousMember159;
    
    /// TS3Functions_requestChannelGroupDel
    public TS3Functions_requestChannelGroupDel AnonymousMember160;
    
    /// TS3Functions_requestChannelGroupAddPerm
    public TS3Functions_requestChannelGroupAddPerm AnonymousMember161;
    
    /// TS3Functions_requestChannelGroupDelPerm
    public TS3Functions_requestChannelGroupDelPerm AnonymousMember162;
    
    /// TS3Functions_requestChannelGroupPermList
    public TS3Functions_requestChannelGroupPermList AnonymousMember163;
    
    /// TS3Functions_requestSetClientChannelGroup
    public TS3Functions_requestSetClientChannelGroup AnonymousMember164;
    
    /// TS3Functions_requestChannelAddPerm
    public TS3Functions_requestChannelAddPerm AnonymousMember165;
    
    /// TS3Functions_requestChannelDelPerm
    public TS3Functions_requestChannelDelPerm AnonymousMember166;
    
    /// TS3Functions_requestChannelPermList
    public TS3Functions_requestChannelPermList AnonymousMember167;
    
    /// TS3Functions_requestClientAddPerm
    public TS3Functions_requestClientAddPerm AnonymousMember168;
    
    /// TS3Functions_requestClientDelPerm
    public TS3Functions_requestClientDelPerm AnonymousMember169;
    
    /// TS3Functions_requestClientPermList
    public TS3Functions_requestClientPermList AnonymousMember170;
    
    /// TS3Functions_requestChannelClientAddPerm
    public TS3Functions_requestChannelClientAddPerm AnonymousMember171;
    
    /// TS3Functions_requestChannelClientDelPerm
    public TS3Functions_requestChannelClientDelPerm AnonymousMember172;
    
    /// TS3Functions_requestChannelClientPermList
    public TS3Functions_requestChannelClientPermList AnonymousMember173;
    
    /// TS3Functions_privilegeKeyUse
    public TS3Functions_privilegeKeyUse AnonymousMember174;
    
    /// TS3Functions_requestPermissionList
    public TS3Functions_requestPermissionList AnonymousMember175;
    
    /// TS3Functions_requestPermissionOverview
    public TS3Functions_requestPermissionOverview AnonymousMember176;
    
    /// TS3Functions_clientPropertyStringToFlag
    public TS3Functions_clientPropertyStringToFlag AnonymousMember177;
    
    /// TS3Functions_channelPropertyStringToFlag
    public TS3Functions_channelPropertyStringToFlag AnonymousMember178;
    
    /// TS3Functions_serverPropertyStringToFlag
    public TS3Functions_serverPropertyStringToFlag AnonymousMember179;
    
    /// TS3Functions_getAppPath
    public TS3Functions_getAppPath AnonymousMember180;
    
    /// TS3Functions_getResourcesPath
    public TS3Functions_getResourcesPath AnonymousMember181;
    
    /// TS3Functions_getConfigPath
    public TS3Functions_getConfigPath AnonymousMember182;
    
    /// TS3Functions_getPluginPath
    public TS3Functions_getPluginPath AnonymousMember183;
    
    /// TS3Functions_getCurrentServerConnectionHandlerID
    public TS3Functions_getCurrentServerConnectionHandlerID AnonymousMember184;
    
    /// TS3Functions_printMessage
    public TS3Functions_printMessage AnonymousMember185;
    
    /// TS3Functions_printMessageToCurrentTab
    public TS3Functions_printMessageToCurrentTab AnonymousMember186;
    
    /// TS3Functions_urlsToBB
    public TS3Functions_urlsToBB AnonymousMember187;
    
    /// TS3Functions_sendPluginCommand
    public TS3Functions_sendPluginCommand AnonymousMember188;
    
    /// TS3Functions_getDirectories
    public TS3Functions_getDirectories AnonymousMember189;
    
    /// TS3Functions_getServerConnectInfo
    public TS3Functions_getServerConnectInfo AnonymousMember190;
    
    /// TS3Functions_getChannelConnectInfo
    public TS3Functions_getChannelConnectInfo AnonymousMember191;
    
    /// TS3Functions_createReturnCode
    public TS3Functions_createReturnCode AnonymousMember192;
    
    /// TS3Functions_requestInfoUpdate
    public TS3Functions_requestInfoUpdate AnonymousMember193;
    
    /// TS3Functions_getServerVersion
    public TS3Functions_getServerVersion AnonymousMember194;
    
    /// TS3Functions_isWhispering
    public TS3Functions_isWhispering AnonymousMember195;
    
    /// TS3Functions_isReceivingWhisper
    public TS3Functions_isReceivingWhisper AnonymousMember196;
    
    /// TS3Functions_getAvatar
    public TS3Functions_getAvatar AnonymousMember197;
    
    /// TS3Functions_setPluginMenuEnabled
    public TS3Functions_setPluginMenuEnabled AnonymousMember198;
    
    /// TS3Functions_showHotkeySetup
    public TS3Functions_showHotkeySetup AnonymousMember199;
    
    /// TS3Functions_requestHotkeyInputDialog
    public TS3Functions_requestHotkeyInputDialog AnonymousMember200;
    
    /// TS3Functions_getHotkeyFromKeyword
    public TS3Functions_getHotkeyFromKeyword AnonymousMember201;
    
    /// TS3Functions_getClientDisplayName
    public TS3Functions_getClientDisplayName AnonymousMember202;
    
    /// TS3Functions_getBookmarkList
    public TS3Functions_getBookmarkList AnonymousMember203;
    
    /// TS3Functions_getProfileList
    public TS3Functions_getProfileList AnonymousMember204;
    
    /// TS3Functions_guiConnect
    public TS3Functions_guiConnect AnonymousMember205;
    
    /// TS3Functions_guiConnectBookmark
    public TS3Functions_guiConnectBookmark AnonymousMember206;
    
    /// TS3Functions_createBookmark
    public TS3Functions_createBookmark AnonymousMember207;
    
    /// TS3Functions_getPermissionIDByName
    public TS3Functions_getPermissionIDByName AnonymousMember208;
    
    /// TS3Functions_getClientNeededPermission
    public TS3Functions_getClientNeededPermission AnonymousMember209;
}
    */
