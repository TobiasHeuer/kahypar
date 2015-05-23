/***************************************************************************
 *  Copyright (C) 2014 Sebastian Schlag <sebastian.schlag@kit.edu>
 **************************************************************************/

#ifndef SRC_PARTITION_CONFIGURATION_H_
#define SRC_PARTITION_CONFIGURATION_H_

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

#include "lib/definitions.h"

using defs::HypernodeWeight;
using defs::HypernodeID;
using defs::HyperedgeID;
using defs::PartitionID;
using defs::HypernodeWeightVector;

namespace partition {
enum class InitialPartitioner {
  hMetis,
  PaToH,
  KaHyPar
};

struct Configuration {
  struct CoarseningParameters {
    CoarseningParameters() :
      max_allowed_node_weight(0),
      contraction_limit(0),
      contraction_limit_multiplier(0),
      hypernode_weight_fraction(0.0),
      max_allowed_weight_multiplier(0.0),
      scheme() { }

    HypernodeWeight max_allowed_node_weight;
    HypernodeID contraction_limit;
    HypernodeID contraction_limit_multiplier;
    double hypernode_weight_fraction;
    double max_allowed_weight_multiplier;
    std::string scheme;
  };

  struct InitialPartitioningParameters {
	  InitialPartitioningParameters() :
		  coarse_graph_filename(),
		  coarse_graph_partition_filename(),
		  k(2),
		  epsilon(0.05),
	  	  mode(),
		  upper_allowed_partition_weight(),
		  perfect_balance_partition_weight(),
		  seed(-1),
		  nruns(1),
		  alpha(1),
		  beta(1),
		  unassigned_part(0),
		  ils_iterations(),
		  rollback(),
		  refinement(),
		  erase_components(),
		  balance(),
		  stats(),
		  styles() { }

	  std::string coarse_graph_filename;
	  std::string coarse_graph_partition_filename;
	  PartitionID k;
	  double epsilon;
	  std::string mode;
	  HypernodeWeightVector upper_allowed_partition_weight;
	  HypernodeWeightVector perfect_balance_partition_weight;
	  int nruns;
	  PartitionID unassigned_part;
	  double alpha;
	  double beta;
	  int seed;
	  int ils_iterations;
	  bool rollback;
	  bool refinement;
	  bool erase_components;
	  bool balance;
	  bool stats;
	  bool styles;
  };

  struct PartitioningParameters {
    PartitioningParameters() :
      k(2),
      seed(0),
      initial_partitioning_attempts(1),
      global_search_iterations(1),
      current_v_cycle(0),
      epsilon(1.0),
      hmetis_ub_factor(-1.0),
      max_part_weight(std::numeric_limits<HypernodeWeight>::max()),
      total_graph_weight(0),
      hyperedge_size_threshold(-1),
      initial_parallel_he_removal(false),
      verbose_output(false),
      initial_partitioner(InitialPartitioner::hMetis),
      graph_filename(),
      graph_partition_filename(),
      coarse_graph_filename(),
      coarse_graph_partition_filename(),
      initial_partitioner_path() { }

    PartitionID k;
    int seed;
    int initial_partitioning_attempts;
    int global_search_iterations;
    int current_v_cycle;
    double epsilon;
    double hmetis_ub_factor;
    HypernodeWeight max_part_weight;
    HypernodeWeight total_graph_weight;
    HyperedgeID hyperedge_size_threshold;
    bool initial_parallel_he_removal;
    bool verbose_output;
    InitialPartitioner initial_partitioner;
    std::string graph_filename;
    std::string graph_partition_filename;
    std::string coarse_graph_filename;
    std::string coarse_graph_partition_filename;
    std::string initial_partitioner_path;
  };

  struct FMParameters {
    FMParameters() :
      max_number_of_fruitless_moves(50),
      num_repetitions(1),
      alpha(4),
      beta(0.0),
      stopping_rule(),
      active(true) { }

    int max_number_of_fruitless_moves;
    int num_repetitions;
    double alpha;
    double beta;
    std::string stopping_rule;
    bool active;
  };

  struct HERFMParameters {
    HERFMParameters() :
      max_number_of_fruitless_moves(10),
      num_repetitions(1),
      stopping_rule(),
      active(false) { }

    int max_number_of_fruitless_moves;
    int num_repetitions;
    std::string stopping_rule;
    bool active;
  };

  struct LPRefinementParameters {
    LPRefinementParameters() :
      max_number_iterations(3),
      active(false) { }

    int max_number_iterations;
    bool active;
  };


  PartitioningParameters partition;
  CoarseningParameters coarsening;
  InitialPartitioningParameters initial_partitioning;
  FMParameters fm_local_search;
  HERFMParameters her_fm;
  LPRefinementParameters lp_refiner;

  Configuration() :
    partition(),
    coarsening(),
    fm_local_search(),
    her_fm(),
    lp_refiner() { }
};

inline std::string toString(const Configuration& config) {
  std::ostringstream oss;
  oss << std::left;
  oss << "Partitioning Parameters:" << std::endl;
  oss << std::setw(35) << "  Hypergraph: " << config.partition.graph_filename << std::endl;
  oss << std::setw(35) << "  Partition File: " << config.partition.graph_partition_filename
  << std::endl;
  oss << std::setw(35) << "  Coarsened Hypergraph: " << config.partition.coarse_graph_filename
  << std::endl;
  oss << std::setw(35) << "  Coarsened Partition File: "
  << config.partition.coarse_graph_partition_filename << std::endl;
  oss << std::setw(35) << "  k: " << config.partition.k << std::endl;
  oss << std::setw(35) << "  epsilon: " << config.partition.epsilon
  << std::endl;
  oss << std::setw(35) << "  total_graph_weight: "
  << config.partition.total_graph_weight << std::endl;
  oss << std::setw(35) << "  L_max: " << config.partition.max_part_weight
  << std::endl;
  oss << std::setw(35) << "  seed: " << config.partition.seed << std::endl;
  oss << std::setw(35) << "  hmetis_ub_factor: " << config.partition.hmetis_ub_factor << std::endl;
  oss << std::setw(35) << "  # initial partitionings: "
  << config.partition.initial_partitioning_attempts << std::endl;
  oss << std::setw(35) << "   initial partitioner: " <<
  (config.partition.initial_partitioner == InitialPartitioner::hMetis ? "hMetis" : "PaToH")
  << std::endl;
  oss << std::setw(35) << "   initial partitioner path: " << config.partition.initial_partitioner_path
  << std::endl;
  oss << std::setw(35) << "  # global search iterations: "
  << config.partition.global_search_iterations << std::endl;
  oss << std::setw(35) << "  hyperedge size threshold: " << config.partition.hyperedge_size_threshold
  << std::endl;
  oss << std::setw(35) << "  initially remove parallel HEs: " << std::boolalpha
  << config.partition.initial_parallel_he_removal << std::endl;
  oss << "Coarsening Parameters:" << std::endl;
  oss << std::setw(35) << "  scheme: " << config.coarsening.scheme << std::endl;
  oss << std::setw(35) << "  max-allowed-weight-multiplier: "
  << config.coarsening.max_allowed_weight_multiplier << std::endl;
  oss << std::setw(35) << "  contraction-limit-multiplier: "
  << config.coarsening.contraction_limit_multiplier << std::endl;
  oss << std::setw(35) << "  hypernode weight fraction: "
  << config.coarsening.hypernode_weight_fraction << std::endl;
  oss << std::setw(35) << "  max. allowed hypernode weight: " << config.coarsening.max_allowed_node_weight
  << std::endl;
  oss << std::setw(35) << "  contraction limit: " << config.coarsening.contraction_limit
  << std::endl;
  if (config.fm_local_search.active) {
    oss << "FM Refinement Parameters:" << std::endl;
    oss << std::setw(35) << "  stopping rule: " << config.fm_local_search.stopping_rule << std::endl;
    oss << std::setw(35) << "  max. # repetitions: " << config.fm_local_search.num_repetitions << std::endl;
    oss << std::setw(35) << "  max. # fruitless moves: "
    << config.fm_local_search.max_number_of_fruitless_moves << std::endl;
    oss << std::setw(35) << "  random walk stop alpha: "
    << config.fm_local_search.alpha << std::endl;
    oss << std::setw(35) << "  random walk stop beta : "
    << config.fm_local_search.beta << std::endl;
  }
  if (config.her_fm.active) {
    oss << "HER-FM Refinement Parameters:" << std::endl;
    oss << std::setw(35) << "  stopping rule: " << config.her_fm.stopping_rule << std::endl;
    oss << std::setw(35) << "  max. # repetitions: " << config.her_fm.num_repetitions << std::endl;
    oss << std::setw(35) << "  max. # fruitless moves: "
    << config.her_fm.max_number_of_fruitless_moves << std::endl;
  }
  if (config.lp_refiner.active) {
    oss << "LP Refinement Parameters:" << std::endl;
    oss << std::setw(35) << "  max. # iterations: " << config.lp_refiner.max_number_iterations << std::endl;
  }
  return oss.str();
}
}  // namespace partition

#endif  // SRC_PARTITION_CONFIGURATION_H_
