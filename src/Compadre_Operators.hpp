#ifndef _COMPADRE_OPERATORS_HPP_
#define _COMPADRE_OPERATORS_HPP_

namespace Compadre {

    //! Available target functionals
    enum TargetOperation {
        //! Point evaluation of a scalar
        ScalarPointEvaluation,
        //! Point evaluation of a vector (reconstructs entire vector at once, requiring a 
        //! ReconstructionSpace having a sufficient number of components in the basis)
        VectorPointEvaluation, 
        //! Point evaluation of the laplacian of a scalar (could be on a manifold or not)
        LaplacianOfScalarPointEvaluation,
        //! Point evaluation of the laplacian of each component of a vector
        LaplacianOfVectorPointEvaluation,
        //! Point evaluation of the gradient of a scalar
        GradientOfScalarPointEvaluation,
        //! Point evaluation of the gradient of a vector (results in a matrix)
        GradientOfVectorPointEvaluation,
        //! Point evaluation of the divergence of a vector (results in a scalar)
        DivergenceOfVectorPointEvaluation,
        //! Point evaluation of the curl of a vector (results in a vector)
        CurlOfVectorPointEvaluation,
        //! Point evaluation of the partial with respect to x of a scalar
        PartialXOfScalarPointEvaluation,
        //! Point evaluation of the partial with respect to y of a scalar
        PartialYOfScalarPointEvaluation,
        //! Point evaluation of the partial with respect to z of a scalar
        PartialZOfScalarPointEvaluation,
        //! Point evaluation of the divergence of vector, but whose partial with respect to z of a scalar
        DivergenceOfScalarPointEvaluation,
        //! Point evaluation of the chained staggered Laplacian acting on VectorTaylorPolynomial 
        //! basis + StaggeredEdgeIntegralSample sampling functional
        ChainedStaggeredLaplacianOfScalarPointEvaluation,
        //! Should be the total count of all available target functionals
        COUNT=13,
    };

    //! Rank of target functional input for each TargetOperation
    const int TargetInputTensorRank[] = {
        0, ///< ScalarPointEvaluation
        1, ///< VectorPointEvaluation
        0, ///< LaplacianOfScalarPointEvaluation
        1, ///< LaplacianOfVectorPointEvaluation
        0, ///< GradientOfScalarPointEvaluation
        1, ///< GradientOfVectorPointEvaluation
        1, ///< DivergenceOfVectorPointEvaluation
        1, ///< CurlOfVectorPointEvaluation
        0, ///< PartialXOfScalarPointEvaluation
        0, ///< PartialYOfScalarPointEvaluation
        0, ///< PartialZOfScalarPointEvaluation
        0, ///< DivergenceOfScalarPointEvaluation
        0, ///< ChainedStaggeredLaplacianOfScalarPointEvaluation
    };

    //! Rank of target functional output for each TargetOperation
    const int TargetOutputTensorRank[] {
        0, ///< PointEvaluation
        1, ///< VectorPointEvaluation
        0, ///< LaplacianOfScalarPointEvaluation
        1, ///< LaplacianOfVectorPointEvaluation
        1, ///< GradientOfScalarPointEvaluation
        1, ///< GradientOfVectorPointEvaluation
        0, ///< DivergenceOfVectorPointEvaluation
        1, ///< CurlOfVectorPointEvaluation
        0, ///< PartialXOfScalarPointEvaluation
        0, ///< PartialYOfScalarPointEvaluation
        0, ///< PartialZOfScalarPointEvaluation
        0, ///< DivergenceOfScalarPointEvaluation
        0, ///< ChainedStaggeredLaplacianOfScalarPointEvaluation
    };

    //! Space in which to reconstruct polynomial
    enum ReconstructionSpace {
        //! Scalar polynomial basis centered at the target site and scaled by sum of basis powers 
        //! e.g. \f$(x-x_t)^2*(y-y_t)*(z-z_t)^3/factorial(2+1+3)\f$ would be a member of 3rd order in 3D, where 
        //! \f$(x_t,y_t,z_t)\f$ is the coordinate of the target site in 3D coordinates.
        ScalarTaylorPolynomial,
        //! Vector polynomial basis having # of components _dimensions, or (_dimensions-1) in the case of manifolds)
        VectorTaylorPolynomial,
        //! Not currently supported
        DivergenceFreeVectorPolynomial,
    };

    //! Number of components in the ReconstructionSpace
    const int ReconstructionSpaceRank[] = {
        0, ///< ScalarTaylorPolynomial
        1, ///< VectorTaylorPolynomial
        1, ///< DivergenceFreeVectorPolynomial
        0, ///< ScalarBernsteinPolynomial
        1, ///< VectorBernsteinPolynomial
    };

    //! Available sampling functionals
    enum SamplingFunctional {
        //! Point evaluations of the scalar source function
        PointSample,
        //! Point evaluations of the entire vector source function
        ManifoldVectorSample,
        //! Point evaluations of the entire vector when the source function is known to be a gradient
        ManifoldGradientVectorSample,
        //! Analytical integral of a gradient source vector is just a difference of the scalar source at neighbor and target
        StaggeredEdgeAnalyticGradientIntegralSample,
        //! Samples consist of the result of integrals of a vector dotted with the tangent along edges between neighbor and target
        StaggeredEdgeIntegralSample,
    };

    //! Rank of sampling functional input for each SamplingFunctional
    const int SamplingInputTensorRank[] = {
        0, ///< PointSample
        1, ///< ManifoldVectorSample
        1, ///< ManifoldGradientVectorSample
        0, ///< StaggeredEdgeAnalyticGradientIntegralSample,
        1, ///< StaggeredEdgeIntegralSample
    };

    //! Rank of sampling functional output for each SamplingFunctional
    const int SamplingOutputTensorRank[] {
        0, ///< PointSample
        1, ///< ManifoldVectorSample
        1, ///< ManifoldGradientVectorSample
        0, ///< StaggeredEdgeAnalyticGradientIntegralSample,
        0, ///< StaggeredEdgeIntegralSample
    };

    //! Whether the SamplingFunctional + ReconstructionSpace results in a nontrivial nullspace requiring SVD
    const int SamplingNontrivialNullspace[] {
        // does the sample over polynomials result in an operator
        // with a nontrivial nullspace requiring SVD
        0, ///< PointSample
        0, ///< ManifoldVectorSample
        0, ///< ManifoldGradientVectorSample
        1, ///< StaggeredEdgeAnalyticGradientIntegralSample,
        1, ///< StaggeredEdgeIntegralSample
    };

    //! Dense solver type, that optionally can also handle manifolds
    enum DenseSolverType {
        //! QR factorization performed on P*sqrt(w) matrix
        QR, 
        //! SVD factorization performed on P*sqrt(w) matrix
        SVD, 
        //! Solve GMLS problem on a manifold (will use QR or SVD to solve the resultant GMLS 
        //! problem dependent on SamplingNontrivialNullspace
        MANIFOLD, 
    };

    //! Available weighting kernel function types
    enum WeightingFunctionType {
        Power,
        Gaussian
    };

    //! Helper function for finding alpha coefficients
    static int getTargetInputIndex(const int operation_num, const int input_component_axis_1, const int input_component_axis_2) {
        const int axis_1_size = (TargetInputTensorRank[operation_num] > 1) ? TargetInputTensorRank[operation_num] : 1;
        return axis_1_size*input_component_axis_1 + input_component_axis_2; // 0 for scalar, 0 for vector;
    }

    //! Helper function for finding alpha coefficients
    static int getTargetOutputIndex(const int operation_num, const int output_component_axis_1, const int output_component_axis_2) {
        const int axis_1_size = (TargetOutputTensorRank[operation_num] > 1) ? TargetOutputTensorRank[operation_num] : 1;
        return axis_1_size*output_component_axis_1 + output_component_axis_2; // 0 for scalar, 0 for vector;
    }

    //static int getSamplingInputIndex(const int operation_num, const int input_component_axis_1, const int input_component_axis_2) {
    //    const int axis_1_size = (SamplingInputTensorRank[operation_num] > 1) ? SamplingInputTensorRank[operation_num] : 1;
    //    return axis_1_size*input_component_axis_1 + input_component_axis_2; // 0 for scalar, 0 for vector;
    //}

    //static int getSamplingOutputIndex(const int operation_num, const int output_component_axis_1, const int output_component_axis_2) {
    //    const int axis_1_size = (SamplingOutputTensorRank[operation_num] > 1) ? SamplingOutputTensorRank[operation_num] : 1;
    //    return axis_1_size*output_component_axis_1 + output_component_axis_2; // 0 for scalar, 0 for vector;
    //}

    //static bool validTargetSpaceSample(TargetOperation to, ReconstructionSpace rs, SamplingFunctional sf) {
    //    // all valid combinations to be added here
    //    return true;
    //}

}; // Compadre

#endif
