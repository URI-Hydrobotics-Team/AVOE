#define KEYWORD_LEN 128


class mission_vppn_t{

	private:

		char keyword[KEYWORD_LEN];
		size_t keyword_len;
		uint8_t type; //main, hold, dr
		float speed;	

	public:

		mission_vppn(const char *keyword_, size_t keyword_len_, uint8_t type_, float speed_);
		~mission_vppn;


};
