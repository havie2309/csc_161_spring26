#include <stdio.h>
#include <string.h>

enum c4_result{
  C4_YELLOW_WINS,
  C4_RED_WINS,
  C4_TIE
};
struct c4_game {
  char* yellowplayer;
  char* redplayer;
  int nummoves;
  enum c4_result result;
};

struct c4_stats {
  int total_moves;
  float average_moves;
  char* longest_game_winner;
  char* shortest_game_winner;
  float yellow_win_rate;
  float red_win_rate;
  float tie_rate;
};

float average_move_count(struct c4_game games[], int num_games){
  int num_moves = 0;
  // Calculate the total moves
  for(int i=0; i < num_games; i++){
    num_moves += games[i].nummoves;
  }

  return (num_moves/num_games);
}

float yellow_win_rate(struct c4_game games[], int num_games){
  float yellowwins = 0;
  // Calculate the total of game that yellow player win
  for(int i=0; i < num_games; i++){
    if(games[i].result == C4_YELLOW_WINS){
      yellowwins +=1;
    }
  }

  return (yellowwins/num_games);
}

char* longest_game_winner(struct c4_game games[], int num_games){
  int mostmoves = 0;
  int index = 0;
  // Update the most moves and its index
  for(int i=0; i < num_games; i++){
    if(games[i].nummoves > mostmoves){
      mostmoves = games[i].nummoves;
      index = i;
    }
  }
  // Return yellowplayer if the longest game winner is yellowplayer, otherwise redplayer
  if(games[index].result == C4_YELLOW_WINS){
    return games[index].yellowplayer;
  }
  else{
    return games[index].redplayer;
  }    
}

struct c4_stats compute_c4_stats(struct c4_game games[], int num_games){
  int total_moves = 0;
  float average_moves = 0;
  char* longest_game_winner = "";
  char* shortest_game_winner = "";
  int most_moves=0;
  int least_moves = 100000000;
  int most_move_index =0;
  int least_move_index =0;
  float yellow_win =0 ;
  float red_win = 0;
  float tie = 0;
  float yellow_win_rate = 0;
  float red_win_rate = 0;
  float tie_rate = 0;
  for (int i = 0; i < num_games; i++){
    // Calculate the total move
    total_moves += games[i].nummoves;

    // Update the most moves and its index
    if(games[i].nummoves > most_moves){
      most_moves = games[i].nummoves;
      most_move_index = i;
    }

    // Update the least moves and its index
    if(games[i].nummoves < least_moves){
      least_moves = games[i].nummoves;
      least_move_index = i;
    }

    // Count the number of games that each player win
    if(games[i].result == C4_YELLOW_WINS){
      yellow_win +=1;
    }

    if(games[i].result == C4_RED_WINS){
      red_win +=1;
    }

    if(games[i].result == C4_TIE){
      tie +=1;
    }
  }
  // Update the avarage move, win rate of each player, and tie rate
  average_moves = total_moves/num_games;
  yellow_win_rate = yellow_win/num_games;
  red_win_rate = red_win/num_games;
  tie_rate = tie/num_games;

  // Update the name of longest game winner and shortest game winner
  if(games[most_move_index].result == C4_YELLOW_WINS){
    longest_game_winner = games[most_move_index].yellowplayer;
  }
  else{
    longest_game_winner = games[most_move_index].redplayer;
  } 

  if(games[least_move_index].result == C4_YELLOW_WINS){
    shortest_game_winner = games[least_move_index].yellowplayer;
  }
  else{
    shortest_game_winner = games[least_move_index].redplayer;
  } 
 
  // Update the struct value
  struct c4_stats c4_stats_result;
  c4_stats_result.total_moves = total_moves;
  c4_stats_result.average_moves = average_moves;
  c4_stats_result.longest_game_winner = longest_game_winner;
  c4_stats_result.shortest_game_winner = shortest_game_winner;
  c4_stats_result.yellow_win_rate = yellow_win_rate;
  c4_stats_result.red_win_rate = red_win_rate;
  c4_stats_result.tie_rate = tie_rate;

  return c4_stats_result;

}



void compute_c4_stats_nocopy(struct c4_game games[], int num_games, struct c4_stats* stats){
  
  int most_moves=0;
  int least_moves = 100000000;
  int most_move_index =0;
  int least_move_index =0;
  float yellow_win =0 ;
  float red_win = 0;
  float tie = 0;
  
  for (int i = 0; i < num_games; i++){
    // Calculate the total move
    stats->total_moves += games[i].nummoves;
    
    // Update the most moves and its index
    if(games[i].nummoves > most_moves){
      most_moves = games[i].nummoves;
      most_move_index = i;
    }
    // Update the leasr moves and its index
    if(games[i].nummoves < least_moves){
      least_moves = games[i].nummoves;
      least_move_index = i;
    }

    // Count the games that yellow win
    if(games[i].result == C4_YELLOW_WINS){
      yellow_win +=1;
    }

    // Count the games that red win
    if(games[i].result == C4_RED_WINS){
      red_win +=1;
    }

    // Count the tie games
    if(games[i].result == C4_TIE){
      tie +=1;
    }
  }

  // Update the avarage move, win rate of each player, and tie rate
  stats->average_moves = stats->total_moves/num_games;
  stats->yellow_win_rate = yellow_win/num_games;
  stats->red_win_rate = red_win/num_games;
  stats->tie_rate = tie/num_games;

  // Update the name of longest game winner and shortest game winner
  if(games[most_move_index].result == C4_YELLOW_WINS){
    stats->longest_game_winner = games[most_move_index].yellowplayer;
  }
  else{
    stats->longest_game_winner = games[most_move_index].redplayer;
  } 

  if(games[least_move_index].result == C4_YELLOW_WINS){
    stats->shortest_game_winner = games[least_move_index].yellowplayer;
  }
  else{
    stats->shortest_game_winner = games[least_move_index].redplayer;
  } 
}



int main() {
  struct c4_game game[5] = {
    {.yellowplayer = "Vy",.redplayer = "Rafay",.nummoves = 5, .result = C4_RED_WINS},
    {.yellowplayer = "Vy",.redplayer = "Rafay",.nummoves = 3, .result = C4_TIE},
    {.yellowplayer = "Vy",.redplayer = "Rafay",.nummoves = 4, .result = C4_YELLOW_WINS},
    {.yellowplayer = "Vy",.redplayer = "Rafay",.nummoves = 6, .result = C4_RED_WINS},
    {.yellowplayer = "Vy",.redplayer = "Rafay",.nummoves = 2, .result = C4_YELLOW_WINS},
  };



  //printf("%s \n",longest_game_winner(game, 5));
  //printf("%f \n",yellow_win_rate(game, 5));

  struct c4_stats stats = compute_c4_stats(game, 5);
  printf("Average Moves: %f \n", stats.average_moves);
  printf("Total moves: %d \n", stats.total_moves);
  printf("Shortest game winner: %s \n", stats.shortest_game_winner);
  printf("Longest game winner: %s \n", stats.longest_game_winner);
  printf("Yellow win rate: %f \n", stats.yellow_win_rate);
  printf("Red win rate: %f \n", stats.red_win_rate);
  printf("Tie rate: %f \n", stats.tie_rate);
  
  printf("\n Stats no copy results \n");
  struct c4_stats stats1;

  memset(&stats1,0,sizeof(stats1));
  compute_c4_stats_nocopy(game,5,&stats1);

  printf("Average Moves: %f \n", stats1.average_moves);
  printf("Total moves: %d \n", stats1.total_moves);
  printf("Shortest game winner: %s \n", stats1.shortest_game_winner);
  printf("Longest game winner: %s \n", stats1.longest_game_winner);
  printf("Yellow win rate: %f \n", stats1.yellow_win_rate);
  printf("Red win rate: %f \n", stats1.red_win_rate);
  printf("Tie rate: %f \n", stats1.tie_rate);
  

}
